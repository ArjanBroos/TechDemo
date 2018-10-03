#include "Vector.h"
#include "Position.h"

Vector::Vector() :
	x(0.f), y(0.f), z(0.f), w(1.f) {}
Vector::Vector(float x, float y, float z) :
	x(x), y(y), z(z), w(0.f) {}
Vector::Vector(float x, float y, float z, float w) :
	x(x), y(y), z(z), w(w) {}
Vector::Vector(const Position& position) :
	x(position.x), y(position.y), z(position.z), w(0.f) {}
Vector::Vector(const Position & position, float w) :
	x(position.x), y(position.y), z(position.z), w(w) {}

Vector::operator float*()
{
	return reinterpret_cast<float*>(this);
}

bool Vector::operator==(const Vector & rhs) const
{
	return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
}

float& Vector::operator[](unsigned index)
{
	return reinterpret_cast<float*>(this)[index];
}

float Dot(const Vector & lhs, const Vector & rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

Vector Cross(const Vector & lhs, const Vector & rhs)
{
	return Vector(
		lhs.y*rhs.z - lhs.z*rhs.y,
		lhs.z*rhs.x - lhs.x*rhs.z,
		lhs.x*rhs.y - lhs.y*rhs.x,
		0.f
	);
}
