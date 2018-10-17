#include "Matrix.h"
#include "Vector.h"

Matrix::Matrix()
{
}

Matrix::Matrix(std::array<float, 16> elements) :
	elements(elements)
{
}

Vector Matrix::Row(unsigned index) const
{
	const unsigned RowWidth = 4;
	const unsigned FirstElementInRow = index * RowWidth;
	Vector vector;
	for (unsigned i = 0; i < RowWidth; i++)
	{
		vector[i] = elements[FirstElementInRow + i];
	}
	return vector;
}

Matrix::operator float*()
{
	return elements.data();
}

bool Matrix::operator==(const Matrix & rhs) const
{
	for (unsigned i = 0; i < 16; i++)
	{
		if (elements[i] != rhs.elements[i])
		{
			return false;
		}
	}
	return true;
}

Vector Matrix::operator*(const Vector & rhs) const
{
	Vector vector;
	for (unsigned i = 0; i < 4; i++)
	{
		vector[i] = Dot(Row(i), rhs);
	}
	return vector;
}

Matrix Matrix::Identity()
{
	return Matrix({
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f });
}

Matrix Matrix::Translation(float x, float y, float z)
{
	return Matrix({
		1.f, 0.f, 0.f, x,
		0.f, 1.f, 0.f, y,
		0.f, 0.f, 1.f, z,
		0.f, 0.f, 0.f, 1.f });
}

Matrix Matrix::Scaling(float x, float y, float z)
{
	return Matrix({
		x,  0.f,  0.f, 0.f,
		0.f, y,   0.f, 0.f, 
		0.f, 0.f, z,   0.f,
		0.f, 0.f, 0.f, 1.f });
}

Matrix Matrix::RotationX(float radians)
{
	return Matrix({
			1.f, 0.f, 0.f, 0.f,
			0.f, cos(radians), -sin(radians), 0.f,
			0.f, sin(radians), cos(radians), 0.f,
			0.f, 0.f, 0.f, 1.f
		});
}

Matrix Matrix::RotationY(float radians)
{
	return Matrix({
		cos(radians), 0.f, sin(radians), 0.f,
		0.f, 1.f, 0.f, 0.f,
		-sin(radians), 0.f, cos(radians), 0.f,
		0.f, 0.f, 0.f, 1.f
		});
}

Matrix Matrix::RotationZ(float radians)
{
	return Matrix({
		cos(radians), -sin(radians), 0.f, 0.f,
		sin(radians), cos(radians), 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f
		});
}
