#include "Matrix.h"

Matrix::Matrix()
{
}

Matrix::Matrix(std::initializer_list<float> elements)
{
	for (size_t i = 0; i < elements.size(); i++)
	{
		this->elements[i] = elements[i]; // TODO: std::array
	}
}

Matrix::operator float*()
{
}

bool Matrix::operator==(const Matrix & rhs) const
{
	return false;
}
