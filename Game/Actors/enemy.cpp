#include <fstream>
#include "enemy.h"
#include "Object/Actor.h"
#include <Math\Math.h>


bool Enemy::Load(const std::string& filename)
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
void Enemy::Update(float dt)
{
	nc::Vector2 direction = m_target->GetTransform().position - m_transform.position;
	nc::Vector2 enemyVelocity = direction.Noramlized() * 100.0;
	Enemy::GetTransform().position = Enemy::GetTransform().position + enemyVelocity * dt;
	Enemy::GetTransform().angle = std::atan2(direction.y, direction.x) + nc::DegreesToRadians(90.0f);



}
