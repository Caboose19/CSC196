#include <fstream>
#include "Boss.h"
#include "Object/Actor.h"
#include <Math\Math.h>
#include "Grahpics/ParticleSystem.h"
#include "Object/Scene.h"
#include "Audio/AudioSystem.h"
#include "../Game.h"

	bool Boss::Load(const std::string& filename)
	{
		bool success = false;
		std::ifstream stream(filename);
		if (stream.is_open())
		{
			success = true;
			Actor::Load(stream);

			stream >> m_thrust;

			stream.close();
		}
		return success;
	}
	void Boss::Update(float dt)
	{
		nc::Vector2 direction;
		if (m_target)
		{
			direction = m_target->GetTransform().position - m_transform.position;
			m_transform.angle = std::atan2(direction.y, direction.x) + nc::DegreesToRadians(90.0f);
		};
		nc::Vector2 BossVelocity = direction.Noramlized() * m_thrust;
		m_transform.position = m_transform.position + BossVelocity * dt;

		m_transform.Update();

	}

	void Boss::OnCollision(Actor* actor)
	{
		
		if (actor->GetType() == eType::PROJECTILE)
		{
			g_audioSystem.PlayAudio("X-wing_Boom");
			m_lives = m_lives - 1;
			if(m_lives <= 0)
			{
				m_destroy = true;


				m_scene->GetGame()->AddPoints(10000);
				
				
			}
			

			nc::Color colors[] = { nc::Color::white,nc::Color::blue, nc::Color::yellow };
			nc::Color color = colors[rand() % 3];

			g_particleSystem.Create(m_transform.position, 0, 180, 30, nc::Color{ 1,1,1 }, 1, 100, 200);

		}
		
	}
