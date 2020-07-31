#pragma once
#include "Object/Actor.h"

	class Player : public nc::Actor
	{
	public:

		enum  class eFIRE
		{
			REGUALR,
			FASTERFIRE,
			DEATHSTARLASE
		};
		Player() {}
		virtual ~Player() {}
		int m_lives{ 3 };

		virtual eType GetType() { return eType::PLAYER; }

		virtual bool Load(const std::string& filename) override;
		virtual void Update(float  dt) override;

		virtual void OnCollision(Actor* actor);

		void SetLives(int life) { m_lives = life; }
		void MinusLives(int life) { m_lives - life; }
		void GetLife() {  m_lives; }
	protected:

		eFIRE m_firetype{ eFIRE::REGUALR };

		float speed{0.0f};
		float rotationRate{360.0f};
		float m_fireRate{ 0.6f };
		float m_fireTimer{0.0f};
		float m_abilitytimer{ 0.0f };
		

		nc::Vector2 velocity;
		float m_angularVelocity;
	};
