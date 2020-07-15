#include "Math/Math.h"
#include "Math/Random.h"
#include "Grahpics\Shape.h"
#include "Actors/enemy.h"
#include "Actors/player.h"
#include "core.h"
#include <string>
#include <iostream>





nc::Enemy enemy;
nc::Player player;

float t{ 0 };

float Roundtime{0};
float frametime;
bool gameOver{ false };

DWORD prevTime;
DWORD deltaTime;


bool Update(float dt) //delta tiime (60 fps) (1/60 = 0.016)
{

	DWORD time = GetTickCount();
	deltaTime = time - prevTime;
	prevTime = time;
	
	frametime = dt;
	Roundtime += dt;


	//if (Roundtime > 15.0f) gameOver = true;

//	if (gameOver) dt = dt * 0.025f;

	t = t + (dt * 5.0f);
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	
	//transform.position.x = nc::Clamp(transform.position.x, 0.0f, 800.0f);
	//transform.position.y = nc::Clamp(transform.position.y, 0.0f, 600.0f);
//	transform.position = nc::Clamp(transform.position, { -5,8 }, { 800,600 });

	player.Update(dt);
	enemy.Update(dt);
	
	
	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f/frametime).c_str());
	graphics.DrawString(10, 30, std::to_string(deltaTime / 1000.0f).c_str());

	float v = (std::sin(t) + 1.0f) * 0.5f;

	nc::Color c = nc::Lerp(nc::Color{ 0,0,1}, nc::Color{ 0,1,1 }, v);
	graphics.SetColor(c);
	nc::Vector2 p = nc::Lerp(nc::Vector2{ 400,300 }, nc::Vector2{ 100,100 }, v);
	graphics.DrawString(p.x, p.y, "Tie Fighter");

	if (gameOver) graphics.DrawString(400, 300, "Game Over!!");

	

	
	player.Draw(graphics);
	enemy.Draw(graphics);
}

int main()
{
	DWORD ticks = GetTickCount();
	std::cout << ticks / 1000 / 60 / 60 << std::endl;
	prevTime = GetTickCount();
	
	
	player.Load("player.txt");
	enemy.Load("enemy.txt");

	enemy.SetTarget(&player);

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}
