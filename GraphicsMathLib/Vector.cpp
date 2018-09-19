#include "Vector.h"
#include "Position.h"

Vector::Vector() :
	x(0.f), y(0.f), z(0.f), w(1.f) {}
Vector::Vector(float x, float y, float z) :
	x(x), y(y), z(z), w(1.f) {}
Vector::Vector(float x, float y, float z, float w) :
	x(x), y(y), z(z), w(w) {}
Vector::Vector(const Position& position) :
	x(position.x), y(position.y), z(position.z), w(1.f) {}
Vector::Vector(const Position & position, float w) :
	x(position.x), y(position.y), z(position.z), w(w) {}

Vector::operator float*()
{
	return reinterpret_cast<float*>(this);
}

float Dot(const Vector & lhs, const Vector & rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
