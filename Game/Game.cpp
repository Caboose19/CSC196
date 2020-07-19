#include "Math/Math.h"
#include "Math/Random.h"
#include "Grahpics\Shape.h"
#include "Actors/enemy.h"
#include "Actors/player.h"
#include "core.h"
#include <list>
#include <string>
#include <iostream>

float spawntimer{ 0 };
std::list<nc::Actor*> actors;
template <typename T>
nc::Actor* GetActor()
{
	nc::Actor* result{ nullptr };

	for (nc::Actor* actor : actors)
	{
		result = dynamic_cast<T*>(actor);
		if (result != nullptr) break;
	}

	return result;
}
template <typename T>
std::vector<nc::Actor*> GetActors()
{
	std::vector<nc::Actor*> results;

	for (nc::Actor* actor : actors)
	{
		T* result = dynamic_cast<T*>(actor);
		if (result)
		{
			results.push_back(result);
		}
	}

	return results;
}

float frametime;

DWORD prevTime;
DWORD deltaTime;


bool Update(float dt) //delta tiime (60 fps) (1/60 = 0.016)
{ 
	frametime = dt;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	
	if (Core::Input::IsPressed(VK_SPACE))
	{
		auto actorsremove = GetActors<Enemy>();

		for (auto actor : actorsremove)
		{
			auto iter = std::find(actors.begin(), actors.end(), actor);
			actors.erase(iter);
		}
	}

	spawntimer += dt;
	if (spawntimer >= 3.0f)
	{
		spawntimer = 0.0f;
		//add enemy to scene
		Enemy* enemy = new Enemy;
		enemy->Load("enemy.txt");
		dynamic_cast<Enemy*>(enemy)->SetTarget(GetActor<Player>());
		enemy->GetTransform().position = nc::Vector2{ nc::random(0,800),nc::random(0,600)};
		dynamic_cast<Enemy*>(enemy)->SetThrust(nc::random(50, 125));
		
		actors.push_back(enemy);
	}
	
	for (nc::Actor* actor : actors)
	{
		actor->Update(dt);
	}
	
	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f/frametime).c_str());

	for (nc::Actor* actor : actors)
	{
		actor->Draw(graphics);
	}
}

int main()
{
	DWORD ticks = GetTickCount();
	std::cout << ticks / 1000 / 60 / 60 << std::endl;
	prevTime = GetTickCount();
	
	Player* player = new Player;
	player->Load("player.txt");
	actors.push_back(player);
	
	for (int i = 0; i < 10; i++)
	{
		Enemy* enemy = new Enemy;
		enemy->Load("enemy.txt");
		dynamic_cast<Enemy*>(enemy)->SetThrust(nc::random(50, 125));
		dynamic_cast<Enemy*>(enemy)->SetTarget(player);
		enemy->GetTransform().position = nc::Vector2{nc::random(0,800),nc::random(0,600)};
		actors.push_back(enemy);
	}
	

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}
