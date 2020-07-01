#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
#include <iostream>

const size_t NUM_POINTS = 40;
float speed = 5.0f;
std::vector<nc::Vector2> points;
nc::Vector2 position{400.0f,300.0f};
bool Update(float dt)
{
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	///Use WASD and arrows
	if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) { position -= nc::Vector2{ 2.0f,0.0f } *speed; }
	if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) { position += nc::Vector2{ 2.0f,0.0f }*speed; }
	if (Core::Input::IsPressed(Core::Input::KEY_DOWN)) { position += nc::Vector2{ 0.0f,2.0f }*speed; }
	if (Core::Input::IsPressed(Core::Input::KEY_UP)) { position -= nc::Vector2{ 0.0f,2.0f }*speed; }

	if (Core::Input::IsPressed('A')) { position -= nc::Vector2{ 1.0f,0.0f }*speed; }
	if (Core::Input::IsPressed('D')) { position += nc::Vector2{ 1.0f,0.0f }*speed; }
	if (Core::Input::IsPressed('S')) { position += nc::Vector2{ 0.0f,1.0f }*speed; }
	if (Core::Input::IsPressed('W')) { position -= nc::Vector2{ 0.0f,1.0f }*speed; }

	//mouse follow 
	int x;
	int y;
	Core::Input::GetMousePos(x, y);

	nc::Vector2 target = nc::Vector2{ x , y };
	nc::Vector2 direction = target - position;
	direction.Normalize();
	position = position + direction *5.0f;

   /*if(Core::Input::IsPressed(Core::Input::BUTTON_LEFT)) {
	int x;
		int y;
		Core::Input::GetMousePos(x, y);

		nc::Vector2 target = nc::Vector2{ x , y };
		nc::Vector2 direction = target - position;

		position = position + direction;
	}*/

	for (nc::Vector2& point: points)
	{
		point = { nc::random(-10.0f, 10.0f), nc::random(-10.0f, 10.0f) };
	}
	return false;
}

void Draw(Core::Graphics& graphics)
{
	graphics.SetColor(RGB(rand() % 256, rand() % 256, rand() % 256));
	//graphics.DrawLine(static_cast<float>(rand() % 800), static_cast<float>(rand() % 600), static_cast<float>(rand() % 800), static_cast<float>(rand() % 600));

	for (size_t i = 0; i < 40 - 1; i++)
	{
		//the size of my object 
		nc::Vector2 p1 = position + points[i]*5.5f;
		nc::Vector2 p2 = position + points[i + 1]*5.5f;

		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}

}

int main()
{
	for (size_t i = 0; i < 40; i++) {
		points.push_back(nc::Vector2{ nc::random(0.0f, 800.0f), nc::random(0.0f, 600.0f) });

	}

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}
