#pragma once
#include "core.h"
#include "Object/Scene.h"


	class Game
	{
	public:
		enum class eState
		{
			INIT,
			TITLE,
			START_GAME,
			PLAYER_DEAD,
			GAME_WAIT,
			GAME,
			BOSS_BATTLE,
			CREDITS,
			GAME_OVER
		};	
		
	public:

		int m_lives{ 3 };
		void Startup();
		void Shutdown();

		bool Update(float dt);
		void Draw(Core::Graphics& graphics);

		void AddPoints(int points) { m_score += points; }
		void SetState(eState state) { m_state = state; }

	protected:
		eState m_state{ eState::TITLE };
	
		int m_score{ 0 };
		float m_spawntimer{ 0 };
		float m_statetimer{ 0 };



		float m_frametime;
		nc::Scene m_scene;
		int BOSS_SPAWN = 1;
		static const int WIDTH;
		static const int HEIGHT;
	};

