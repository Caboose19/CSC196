#pragma once
#pragma once
#include "Grahpics/Shape.h"
#include <iostream>
namespace nc
{
	class Actor
	{
	public:
		Actor() {}
		Actor(const Transform& transform, const Shape& shape) :m_transform{ transform }, m_shape{ shape } {}
		~Actor() {}

		bool Load(const std::string& filename);

		void Update(float dt);
		void Draw(Core::Graphics& graphics);

		Transform& GetTransform() { return m_transform; } // return the transform;
		Shape& GetShape() { return m_shape; }// return the shape


	private:
		Transform m_transform;
		Shape m_shape;
	};
}



