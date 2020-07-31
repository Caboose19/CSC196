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
			PROJECTILE,
			LOCATOR,
			TIE,
			FASTERFIRE,
			BOSS,
			DEATHSTARLASER
		};

	public:
		Actor() {}
		Actor(const Transform& transform, const Shape& shape) :m_transform{ transform }, m_shape{ shape } {}
		virtual ~Actor() {}

		virtual void Destroy();


		virtual eType GetType() = 0;


		virtual bool Load(const std::string& filename);
		virtual void Load(std::istream& stream);

		virtual	void Update(float dt);
		virtual void Draw(Core::Graphics& graphics);


		virtual void OnCollision(Actor* actor) {};

		void SetDestroy(bool destroy = true) { m_destroy = destroy; }
		bool IsDestory() { return m_destroy; }

		float GetRadius();

		void SetScene(Scene* scene) { m_scene = scene; }
		Transform& GetTransform() { return m_transform; } // return the transform;
		Shape& GetShape() { return m_shape; }// return the shape

		void AddChild(Actor* child);
		Actor* GetParent() { return m_parent; }

	protected:
		bool m_destroy{ false };
		class Scene* m_scene{ nullptr };
		Transform m_transform;
		Shape m_shape;


		Actor* m_parent{ nullptr };
		std::vector<Actor*>m_children;
		
	};
}



