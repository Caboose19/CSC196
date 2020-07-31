#pragma once
#include "Object/Actor.h"

class DeathStar : public nc::Actor
{	
public:
	DeathStar() {}
	virtual ~DeathStar() {}

	virtual eType GetType() { return eType::DEATHSTARLASER; }

	virtual bool Load(const std::string& filename) override;
	virtual void Update(float  dt) override;

	virtual void OnCollision(Actor* actor);

	void SetThrust(float thrust) { m_thrust; }

	void SetTarget(Actor* actor) { m_target = actor; }

protected:
	float m_thrust{ 0.0f };
	Actor* m_target{ nullptr };

};
