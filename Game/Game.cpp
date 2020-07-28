#include "Math/Math.h"
#include "Math/Random.h"
#include "Grahpics\Shape.h"
#include "Actors/enemy.h"
#include "Actors/player.h"
#include "Grahpics/ParticleSystem.h"
#include "Game.h"
#include <list>
#include <string>
#include <iostream>


	const int Game::WIDTH = 800;
	const int Game::HEIGHT = 600;
	void Game::Startup()
	{
		m_scene.Startup();
		g_particleSystem.Startup();


		Player* player = new Player;
		player->Load("player.txt");
		m_scene.AddActor(player);
	

		for (int i = 0; i < 10; i++)
		{
			Enemy* enemy = new Enemy;
			enemy->Load("enemy.txt");
			enemy->SetTarget(m_scene.GetActor<Player>());
			enemy->GetTransform().position = nc::Vector2{ nc::random(0,800),nc::random(0,600) };
			m_scene.AddActor(enemy);
			//actors.push_back(enemy);
		}
	}
	
	void Game::Shutdown()
	{
		m_scene.Shutdown();
		g_particleSystem.Shutdown(); 
	}

	bool Game::Update(float dt)
	{


		m_frametime = dt;

		bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

		/*if (Core::Input::IsPressed(VK_SPACE))
		{
			auto actorsremove = GetActors<Enemy>();

			for (auto actor : actorsremove)
			{
				auto iter = std::find(actors.begin(), actors.end(), actor);
				actors.erase(iter);
			}
		}*/

		m_spawntimer += dt;
		if (m_spawntimer >= 3.0f)
		{
			m_spawntimer = 0.0f;
			//add enemy to m_scene
			Enemy* enemy = new Enemy;
			enemy->Load("enemy.txt");
			enemy->SetTarget(m_scene.GetActor<Player>());
			enemy->GetTransform().position = nc::Vector2{ nc::random(0,800),nc::random(0,600) };
			m_scene.AddActor(enemy);
		}



		/*if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
		{
			int x, y;
			Core::Input::GetMousePos(x, y);
	
			nc::Color colors[] = { nc::Color::white,nc::Color::blue, nc::Color::yellow };
			nc::Color color = colors[rand() % 3];
	
			g_particleSystem.Create(nc::Vector2{ x,y }, 0, 180, 30, nc::Color{ 1,1,1 }, 1, 100, 200);
		}*/
	
	
	

		g_particleSystem.Update(dt);
		m_scene.Update(dt);



		return quit;
	
	}

	void Game::Draw(Core::Graphics& graphics)
	{

		graphics.DrawString(10, 10, std::to_string(m_frametime).c_str());
		graphics.DrawString(10, 10, std::to_string(m_frametime).c_str());
		graphics.DrawString(10, 20, std::to_string(1.0f / m_frametime).c_str());
	
		m_scene.Draw(graphics);
		g_particleSystem.Draw(graphics);
	
	}
