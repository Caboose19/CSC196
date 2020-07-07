#include "pch.h"
#include "Vector2.h"
#include <string>


namespace nc
{

	const Vector2 Vector2::Left{-1,0};
	const Vector2 Vector2::Right{ 1,0 };
	const Vector2 Vector2::Up{0,-1};
	const Vector2 Vector2::Down{0,1};
	const Vector2 Vector2::Forward{0,-1};

	std::istream& operator >> (std::istream& stream, Vector2& v)
	{
		std::string line;
		std::getline(stream, line);

		if (line.find("{") != std::string::npos)
		{
			std::string vx = line.substr(line.find("{") + 1, line.find(",") - line.find("{") - 1);
			v.x = std::stof(vx);
			std::string vy = line.substr(line.find(",") + 1, line.find("}") - line.find(",") - 1);
			v.y = std::stof(vy);
		}
		return stream;
	}

}

