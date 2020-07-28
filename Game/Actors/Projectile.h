#pragma once
#include "Object/Actor.h"

class Projectile : public nc::Actor
{	
public:
	Projectile() {}
	virtual ~Projectile() {}

	virtual eType GetType() { return eType::PROJECTILE; }

	virtual bool Load(const std::string& filename) override;
	virtual void Update(float  dt) override;

	void OnCollision(Actor* actor);

	void SetThrust(float thrust) { m_thrust; }



protected:
	float m_thrust{ 0.0f };
	float m_lifetime{ 2 };

};
