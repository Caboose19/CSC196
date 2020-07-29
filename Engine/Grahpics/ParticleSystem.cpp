#include "pch.h"
#include "ParticleSystem.h"
#include "Math/Math.h"
#include "Math/Random.h"


nc::particlesystem g_particleSystem;

namespace nc
{
	void particlesystem::Startup()
	{
		m_size = 3000;

		m_particles = new Particle[m_size];
	
	}

	void particlesystem::Shutdown()
	{
		delete[] m_particles;
	}

	void particlesystem::Update(float dt)
	{
		for (size_t i = 0; i < m_size; i++)
		{
			Particle* p = &m_particles[i];
			if (p->activate)
			{
				p->lifetime = p->lifetime - dt;
				p->activate = (p->lifetime > 0);

				p->prevPosition = p->position;
				p->position = p->position + (p->velocity * dt);
				p->velocity = p->velocity * p->damping;
			}
		}
	}

	void particlesystem::Draw(Core::Graphics& graphics)
	{
		for (size_t i = 0; i < m_size; i++)
		{
			Particle* p = &m_particles[i];
			if (p->activate)
			{
				graphics.SetColor(p->color);
				graphics.DrawLine(p->position.x, p->position.y, p->prevPosition.x, p->prevPosition.y);
			}
		}
	}

	void particlesystem::Create(const Vector2& position, float angle, float angleRange, size_t count,
								const Color& color, float lifetime, float speedMin, float speedMax)
	{
		for (size_t i = 0; i < count; i++)
		{
			Particle* p = GetFreePArticle();
			if (p)
			{
				p->activate = true;
				p->lifetime = lifetime;
				p->position = position;
				p->prevPosition = position;
				p->color = color;

				float angleRandom = nc::DegreesToRadians(nc::random(-angleRange, angleRange));
				Vector2 direction = Vector2::Rotate(Vector2::Forward, angle + angleRandom);
				p->velocity = direction * nc::random(speedMin, speedMax);
			}
		}
	}
	Particle* particlesystem::GetFreePArticle()
	{

		Particle* freeParticle{ nullptr };

		for (size_t i = 0; i < m_size; i++)
		{
			Particle* p = &m_particles[i];
			if (!p->activate)
			{
				freeParticle = p;
				break;

			}
		}

		return freeParticle;
	}
}

