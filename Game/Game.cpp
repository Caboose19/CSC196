#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Grahpics\Shape.h"
#include "core.h"
#include <string>
#include <iostream>



const size_t NUM_POINTS = 40;
float speed = 300;


std::vector<nc::Vector2> points = { { 0, -8 }, { 5, 8 }, { 0, 8 }, { -5, 8 }, { 0, -8 } };
nc::Color color{ 0,1,1 };
nc::Shape ship;


nc::Vector2 position{400.0f,300.0f};
float scale = 4.0f;
float angle = 0.0f;

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

	if (Roundtime > 5.0f) gameOver = true;

	if (gameOver) dt = dt * 0.025f;



	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	///Use WASD rotate and arrows move
	/*if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) { position -= nc::Vector2{ 2.0f,0.0f } *speed; }
	if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) { position += nc::Vector2{ 2.0f,0.0f }*speed; }
	if (Core::Input::IsPressed(Core::Input::KEY_DOWN)) { position += nc::Vector2{ 0.0f,2.0f }*speed; }
	if (Core::Input::IsPressed(Core::Input::KEY_UP)) { position -= nc::Vector2{ 0.0f,2.0f }*speed; }
	*/


	nc::Vector2 force;
	if (Core::Input::IsPressed('W')) {
		force = nc::Vector2::Forward * speed * dt;
		nc::Vector2 direction = force;
		direction = nc::Vector2::Rotate(direction, angle);
		position = position + direction;
	}


	if (Core::Input::IsPressed('A')) {angle = angle -(dt * 3.0f); }
	if (Core::Input::IsPressed('D')) { angle = angle + (dt * 3.0f); }
	//if (Core::Input::IsPressed('S')) { position += nc::Vector2::Up*speed*dt; }
	//if (Core::Input::IsPressed('W')) { position -= nc::Vector2::Down*speed*dt; }
	
	//mouse follow 
	/*int x;
	int y;
	Core::Input::GetMousePos(x, y);

	nc::Vector2 target = nc::Vector2{ x , y };
	nc::Vector2 direction = target - position;
	direction.Normalize();
	
	//position = position + direction *5.0f;

	*/
	return false;
}

void Draw(Core::Graphics& graphics)
{
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f/frametime).c_str());
	graphics.DrawString(10, 30, std::to_string(deltaTime / 1000.0f).c_str());


	if (gameOver) graphics.DrawString(400, 300, "Game Over");

	ship.Draw(graphics, position, scale, angle);

}

int main()
{
	DWORD ticks = GetTickCount();
	std::cout << ticks / 1000 / 60 / 60 << std::endl;
	prevTime = GetTickCount();

	ship.Load("ship.txt");
	ship.SetColor(nc::Color{ 1,1,1 });

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}
