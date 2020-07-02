#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
#include <iostream>
#include "Math/Color.h"



const size_t NUM_POINTS = 40;
float speed = 5;

std::vector<nc::Vector2> points = { { 0, -3 }, { 3, 3 }, { 0, 1 }, { -3, 3 }, { 0, -3 } };
nc::Color color{ 0,1,1 };



nc::Vector2 position{400.0f,300.0f};
float scale = 4.0f;
float angle = 0.0f;

bool Update(float dt)
{
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	///Use WASD rotate and arrows move
	/*if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) { position -= nc::Vector2{ 2.0f,0.0f } *speed; }
	if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) { position += nc::Vector2{ 2.0f,0.0f }*speed; }
	if (Core::Input::IsPressed(Core::Input::KEY_DOWN)) { position += nc::Vector2{ 0.0f,2.0f }*speed; }
	if (Core::Input::IsPressed(Core::Input::KEY_UP)) { position -= nc::Vector2{ 0.0f,2.0f }*speed; }
	*/
	if (Core::Input::IsPressed('A')) {angle = angle -dt; }
	if (Core::Input::IsPressed('D')) { angle = angle + dt; }
	//if (Core::Input::IsPressed('S')) { position += nc::Vector2{ 0.0f,1.0f }*speed; }
	//if (Core::Input::IsPressed('W')) { position -= nc::Vector2{ 0.0f,1.0f }*speed; }
	
	//mouse follow 
	int x;
	int y;
	Core::Input::GetMousePos(x, y);

	nc::Vector2 target = nc::Vector2{ x , y };
	nc::Vector2 direction = target - position;
	direction.Normalize();
	
	//position = position + direction *5.0f;

   /*if(Core::Input::IsPressed(Core::Input::BUTTON_LEFT)) {
	int x;
		int y;
		Core::Input::GetMousePos(x, y);

		nc::Vector2 target = nc::Vector2{ x , y };
		nc::Vector2 direction = target - position;

		position = position + direction;
	}*/

	//for (nc::Vector2& point: points)
	//{
	//	point = { nc::random(-10.0f, 10.0f), nc::random(-10.0f, 10.0f) };
	//}
	return false;
}

void Draw(Core::Graphics& graphics)
{
	//rgb (8bits/1byte, 8, 8)(0-255,0-255,0-255)

	graphics.SetColor(color);
	
	for (size_t i = 0; i < points.size() - 1; i++)
	{
		//the size of my object		
		nc::Vector2 p1 = points[i];
		nc::Vector2 p2 =  points[i + 1];

		//scale 
		p1 = p1 * scale;
		p2 = p2 * scale; 

		//rotate
		p1 = nc::Vector2::Rotate(p1, angle);
		p2 = nc::Vector2::Rotate(p2, angle);

		//translate
		p1 = p1 + position;
		p2 = p2 + position;

		

		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}

}

int main()
{
	

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}
