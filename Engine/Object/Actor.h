#pragma once
#pragma once
#include "Grahpics/Shape.h"
#include <iostream>
#include "Object/Scene.h"
namespace nc
{
	class Actor
	{
	public:
		enum  class eType
		{
			PLAYER,
			ENEMY,
			PROJECTILE
		};

	public:
		Actor() {}
		Actor(const Transform& transform, const Shape& shape) :m_transform{ transform }, m_shape{ shape } {}
		virtual ~Actor() {}

		virtual eType GetType() = 0;
	

		virtual bool Load(const std::string& filename);
		virtual void Load(std::istream& stream);
	
		virtual	void Update(float dt);
		virtual void Draw(Core::Graphics& graphics);


		virtual void OnCollision(Actor* actor) {}

		void SetDestroy(bool destroy = true) { m_destory = destroy; }
		bool IsDestory() { return false; }

		float GetRadius();

		void SetScene(Scene* scene) { m_scene = scene; }
		Transform& GetTransform() { return m_transform; } // return the transform;
		Shape& GetShape() { return m_shape; }// return the shape

		

	protected:
		bool m_destory{ false };
		class Scene* m_scene{ nullptr };
		Transform m_transform;
		Shape m_shape;
	};
}



