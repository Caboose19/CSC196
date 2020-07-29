#include <fstream>
#include "Projectile.h"
#include "Object/Actor.h"
#include <Math\Math.h>
#include "Grahpics/ParticleSystem.h"

bool Projectile::Load(const std::string& filename)
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
void Projectile::Update(float dt)
{
	m_lifetime -= dt;

	if (m_lifetime <= 0) m_destroy;

	nc::Vector2 direction = nc::Vector2::Rotate(nc::Vector2::Forward, m_transform.angle);
	nc::Vector2 velocity = direction * m_thrust;
	m_transform.position = m_transform.position + velocity * dt;
 

	g_particleSystem.Create(m_transform.position, m_transform.angle, nc::PI, 1, 
		nc::Color::red,1, 5, 20);

	//if (m_transform.position.x > 800 || m_transform.position.x < 0) m_destory = true;
	
	m_transform.Update();

}
void Projectile::OnCollision(Actor* actor)
{
	if (actor->GetType() == eType::ENEMY)
	{
		m_destroy = true;


	}
}