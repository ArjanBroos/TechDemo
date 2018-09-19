#pragma once

struct Position
{
	float x, y, z;

	Position();
	Position(float x, float y, float z);
	Position(const Position& other);

	operator float*();
};