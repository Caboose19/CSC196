#pragma once
#include "core.h"
#include "Object/Scene.h"
class Game
{
public:
	void Startup();
	void Shutdown();

	bool Update(float dt);
	void Draw(Core::Graphics& graphics);

protected:
	int m_lives{ 3 };
	int m_score{ 0 };
	float m_spawntimer{ 0 };

	float m_frametime;
	nc::Scene m_scene;

	static const int WIDTH;
	static const int HEIGHT;
};

