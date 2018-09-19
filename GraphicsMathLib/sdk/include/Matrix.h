#pragma once

#include <initializer_list>

struct Matrix
{
	float elements[16];

	Matrix();
	Matrix(std::initializer_list<float> elements);

	operator float*();
	bool operator==(const Matrix& rhs) const;
};