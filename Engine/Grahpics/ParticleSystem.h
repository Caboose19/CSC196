#pragma once
#include "Particle.h"
#include "Core.h"

namespace nc
{
	class particlesystem
	{
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);
		void Draw(Core::Graphics& graphics);

		void Create(const Vector2& position, float angle, float angleRange, size_t count, const Color& color,float lifetime, float speedMin, float speedMax );

	protected:
		Particle* GetFreePArticle();

	protected:
		Particle* m_particles;
		size_t m_size;


	};
}

extern nc::particlesystem g_particleSystem;