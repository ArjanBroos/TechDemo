#include "Position.h"

Position::Position() : 
	x(0.f), y(0.f), z(0.f) {}
Position::Position(float x, float y, float z) :
	x(x), y(y), z(z) {}
Position::Position(const Position& other) : 
	x(other.x), y(other.y), z(other.z) {}

Position::operator float*() 
{
	return reinterpret_cast<float*>(this); 
}