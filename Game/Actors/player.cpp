#include <fstream>
#include "player.h"
#include "Object/Actor.h"
#include "Projectile.h"
#include "Object/Scene.h"
#include <Math\Math.h>
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
	m_fireTimer += dt;

	if (Core::Input::IsPressed(VK_SPACE) && m_fireTimer >= m_fireRate){

	m_fireTimer = 0;
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


	if (Core::Input::IsPressed('A')) { m_transform.angle = m_transform.angle - (nc::DegreesToRadians(360.0f) * dt); }
	if (Core::Input::IsPressed('D')) { m_transform.angle = m_transform.angle + (nc::DegreesToRadians(360.0f) * dt); }

	if (m_transform.position.x > 800) m_transform.position.x = 0;
	if (m_transform.position.x < 0) m_transform.position.x = 800;
	if (m_transform.position.y < 0) m_transform.position.y = 600;
	if (m_transform.position.y > 600) m_transform.position.y = 0;


	if (force.LengthSqr() > 0)
	{
		g_particleSystem.Create(m_transform.position, m_transform.angle, nc::PI, 1, nc::Color::yellow, 1, 50, 100);
	}

	m_transform.Update();
}
