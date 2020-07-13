#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/transform.h"
#include "Math/Color.h"
#include "Grahpics\Shape.h"
#include "Object/Actor.h"
#include "core.h"
#include <string>
#include <iostream>


float speed = 3;

nc::Vector2 velocity;
nc::Color color(0.0f, 25.0f, 1.0f);

nc::Shape ship;
nc::Transform transform{ {400,300},{10},{0} };

nc::Actor player;
nc::Actor enemy;


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

	

	if (Roundtime > 15.0f) gameOver = true;

	if (gameOver) dt = dt * 0.025f;

	t = t + (dt * 5.0f);

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	///Use WASD rotate and arrows move
	/*if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) { position -= nc::Vector2{ 2.0f,0.0f } *speed; }
	if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) { position += nc::Vector2{ 2.0f,0.0f }*speed; }
	if (Core::Input::IsPressed(Core::Input::KEY_DOWN)) { position += nc::Vector2{ 0.0f,2.0f }*speed; }
	if (Core::Input::IsPressed(Core::Input::KEY_UP)) { position -= nc::Vector2{ 0.0f,2.0f }*speed; }
	*/


	nc::Vector2 force{0,0};
	if (Core::Input::IsPressed('W')) {
		force = nc::Vector2::Forward * speed;
	}
	
		force = nc::Vector2::Rotate(force, player.GetTransform().angle);
		velocity = velocity + (force + dt);
		velocity = velocity * 0.99f;
		player.GetTransform().position = player.GetTransform().position + (velocity * dt);


	if (Core::Input::IsPressed('A')) {player.GetTransform().angle = player.GetTransform().angle -  (nc::DegreesToRadians(360.0f) * dt); }
	if (Core::Input::IsPressed('D')) { player.GetTransform().angle = player.GetTransform().angle + (nc::DegreesToRadians(360.0f) * dt); }
	
	if (player.GetTransform().position.x > 800) player.GetTransform().position.x = 0;
	if (player.GetTransform().position.x < 0) player.GetTransform().position.x = 800;
	if (player.GetTransform().position.y < 0) player.GetTransform().position.y = 600;
	if (player.GetTransform().position.y > 600) player.GetTransform().position.y = 0;

	//transform.position.x = nc::Clamp(transform.position.x, 0.0f, 800.0f);
	//transform.position.y = nc::Clamp(transform.position.y, 0.0f, 600.0f);
//	transform.position = nc::Clamp(transform.position, { -5,8 }, { 800,600 });


	///enemy
	nc::Vector2 direction = player.GetTransform().position - enemy.GetTransform().position;
	nc::Vector2 enemyVelocity = direction.Noramlized() * 100.0;
	enemy.GetTransform().position = enemy.GetTransform().position + enemyVelocity * dt;
	enemy.GetTransform().angle = std::atan2(direction.y, direction.x) + nc::DegreesToRadians(90.0f);


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

	

	//ship.Draw(graphics, transform);
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
	ship.Load("ship.txt");
	//ship.SetColor(color);

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}
