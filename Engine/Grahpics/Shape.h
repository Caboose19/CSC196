#pragma once
#include "core.h"
#include "../Math/Vector2.h"
#include "../Math/Color.h"
#include <vector>


namespace nc
{
	class Shape
	{
	public:
		Shape() {}
		Shape(const std::vector<nc::Vector2>& points, const Color& color) {}

		void Draw(Core::Graphics& graphics);

		void Draw(Core::Graphics& graphics, nc::Vector2 position, float scale = 1.0f, float angle = 0.0f);
		void SetColor(Color color);
		const Color& GetColor() const;

	

	private:
		std::vector<nc::Vector2> points;
		Color color;

	};

	void Shape::Draw(Core::Graphics& graphics)
	{
		

			for (size_t i = 0; i < points.size() - 1; i++)
			{
				// local / object space points
				nc::Vector2 p1 = points[i];
				nc::Vector2 p2 = points[i + 1];

				// transform points

				// draw points
			}
	}

}