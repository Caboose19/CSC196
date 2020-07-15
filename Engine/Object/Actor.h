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

	virtual bool Load(const std::string& filename);

	virtual	void Update(float dt);
	virtual void Draw(Core::Graphics& graphics);

	virtual void Load(std::istream& stream);

		Transform& GetTransform() { return m_transform; } // return the transform;
		Shape& GetShape() { return m_shape; }// return the shape


	protected:
		Transform m_transform;
		Shape m_shape;
	};
}



