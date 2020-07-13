#include "pch.h"
#include "transform.h"
namespace nc
{
	std::istream& operator>>(std::istream& stream, Transform& transform)
	{

		stream >> transform.position;
		std::string line;
		std::getline(stream, line);
		transform.scale = stof(line);

		std::getline(stream, line);
		transform.angle = stof(line);
		



		return stream;
	}

}
