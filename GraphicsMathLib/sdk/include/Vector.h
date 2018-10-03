#pragma once

struct Position;

struct Vector
{
	float x, y, z, w;

	Vector();
	Vector(float x, float y, float z);
	Vector(float x, float y, float z, float w);
	Vector(const Position& position);
	Vector(const Position& position, float w);

	operator float*();
	bool operator==(const Vector& rhs) const;
	float& operator[](unsigned index);
};

float Dot(const Vector& lhs, const Vector& rhs);
Vector Cross(const Vector& lhs, const Vector& rhs);