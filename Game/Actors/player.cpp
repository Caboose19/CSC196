#include <fstream>
#include "player.h"
#include "Object/Actor.h"
#include <Math\Math.h>

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

}
