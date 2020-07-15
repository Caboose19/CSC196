#pragma once
#include "Object/Actor.h"
namespace nc
{
	class Player : public nc::Actor
	{
	public:
		Player() {}
		virtual ~Player() {}

		virtual bool Load(const std::string& filename) override;
		virtual void Update(float  dt) override;

	protected:
		float speed;
		float rotationRate;
		Vector2 velocity;
		//thrust (float)
		// rotation rate (float)
		// velocity (Vector2)

	};
}