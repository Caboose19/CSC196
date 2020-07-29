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

	void Transform::Update()
	{
		Matrix33 mxScale;
		mxScale.scale(scale);
		
		Matrix33 mxRotate;
		mxRotate.Rotate(angle);

		Matrix33 mxt;
		mxt.Translation(position);

		matrix = mxScale * mxRotate * mxt;
	}

	void Transform::Update(const Matrix33& mx)
	{
		Matrix33 mxScale;
		mxScale.scale(scale);

		Matrix33 mxRotate;
		mxRotate.Rotate(angle);

		Matrix33 mxt;
		mxt.Translation(position);

		matrix = mxScale * mxRotate * mxt *mx;
	}

}
