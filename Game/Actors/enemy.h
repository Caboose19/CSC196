#pragma once
#pragma once
#include "Object/Actor.h"
namespace nc
{
	class Enemy : public nc::Actor
	{


		virtual	bool Load(const std::string& filename);

		virtual	void Update(float dt);
		void Draw(Core::Graphics& graphics);

	};
}