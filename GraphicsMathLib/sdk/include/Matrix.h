#pragma once

#include <array>

struct Vector;

struct Matrix
{
	std::array<float, 16> elements;

	Matrix();
	Matrix(std::array<float, 16> elements);

	Vector Row(unsigned index) const;

	operator float*();
	bool operator==(const Matrix& rhs) const;
	Vector operator*(const Vector& rhs) const;

	static Matrix Identity();
	static Matrix Translation(float x, float y, float z);
	static Matrix Scaling(float x, float y, float z);
};