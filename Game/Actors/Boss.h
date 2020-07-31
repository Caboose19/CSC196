#pragma once
#include "Object/Actor.h"

class Boss : public nc::Actor
{	
public:
	Boss() {}
	virtual ~Boss() {}

	virtual eType GetType() { return eType::BOSS; }

	virtual bool Load(const std::string& filename) override;
	virtual void Update(float  dt) override;

	virtual void OnCollision(Actor* actor);

	void SetThrust(float thrust) { m_thrust; }

	void SetTarget(Actor* actor) { m_target = actor; }

protected:
	float m_thrust{ 0.0f };
	Actor* m_target{ nullptr };
	int m_lives{ 5 };

};
