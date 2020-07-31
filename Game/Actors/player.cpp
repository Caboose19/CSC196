#include <fstream>
#include "player.h"
#include "Object/Actor.h"
#include "Projectile.h"
#include "Audio/AudioSystem.h"
#include "../Game.h"
#include <Math\Math.h>
#include "Object/Scene.h"
#include "Grahpics/ParticleSystem.h"

	bool Player::Load(const std::string& filename)
	{
		bool success = false;

		std::ifstream stream(filename);
		if (stream.is_open())
		{
			success = true;

			Actor::Load(stream);

			stream >> speed;
			stream >> rotationRate;

			stream.close();
		}
		return success;
	}
	void Player::Update(float dt)
	{
	
		m_abilitytimer += dt;
		m_fireTimer += dt;
		if (m_abilitytimer >= 5.0f)
		{
			m_fireRate = 0.6f;
		}
		if (Core::Input::IsPressed(VK_SPACE) && m_fireTimer >= m_fireRate)
		{

		m_fireTimer = 0;
		g_audioSystem.PlayAudio("Laser");

		Projectile*projectile = new Projectile;
		projectile->Load("Projectile.txt");
		projectile->GetTransform().position = m_transform.position;
		projectile->GetTransform().angle = m_transform.angle;

		m_scene->AddActor(projectile);
		}

		//position
		nc::Vector2 force{ 0,0 };

		if (Core::Input::IsPressed('W')) {
			force = nc::Vector2::Forward * speed;
		}
		
		force = nc::Vector2::Rotate(force, m_transform.angle);
		velocity = velocity + (force + dt);
		velocity = velocity * 0.99f;
		m_transform.position = m_transform.position + (velocity * dt);

		float torque = 0;
		if (Core::Input::IsPressed('A')) { torque = -nc::DegreesToRadians(rotationRate); }
		if (Core::Input::IsPressed('D')) { torque = nc::DegreesToRadians(rotationRate); }

		m_angularVelocity = m_angularVelocity + torque * dt;
		m_angularVelocity = m_angularVelocity * 0.95f;
		m_transform.angle = m_transform.angle + m_angularVelocity * dt;

		if (m_transform.position.x > 800) m_transform.position.x = 0;
		if (m_transform.position.x < 0) m_transform.position.x = 800;
		if (m_transform.position.y < 0) m_transform.position.y = 600;
		if (m_transform.position.y > 600) m_transform.position.y = 0;


		if (force.LengthSqr() > 0)
		{
			Actor* locator = m_children[0];
			g_particleSystem.Create(locator->GetTransform().matrix.GetPosition(),
				locator->GetTransform().matrix.GetAngle() + nc::PI,1,20, nc::Color::yellow, 1, 50, 100);

			 locator = m_children[1];
			g_particleSystem.Create(locator->GetTransform().matrix.GetPosition(),
				locator->GetTransform().matrix.GetAngle() + nc::PI, 1, 20, nc::Color::yellow, 1, 50, 100);
		}

		m_transform.Update();

		for (Actor* child : m_children)
		{
			child->Update(dt);
		}
	}

	void Player::OnCollision(Actor* actor)
	{
		if (actor->GetType() == eType::ENEMY|| actor->GetType() == eType::BOSS)
		{
			m_scene->GetGame()->SetState(Game::eState::PLAYER_DEAD);
			m_destroy = true;

			nc::Color colors[] = { nc::Color::red,nc::Color::blue, nc::Color::yellow };
			nc::Color color = colors[rand() % 3];

			g_particleSystem.Create(m_transform.position, 0, 180, 30, nc::Color{ 1,1,1 }, 1, 100, 200);
		}
		if (actor->GetType() == eType::DEATHSTARLASER)
		{
			
			m_abilitytimer = 0.0f;
			m_fireRate = 0.00000000001f;
		
		}
		if (actor->GetType() == eType::FASTERFIRE)
		{
			Game game;
			game.m_lives += 1;

		}
	}
