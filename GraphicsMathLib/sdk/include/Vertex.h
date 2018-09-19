#pragma once

#include "Position.h"
#include "Color.h"

struct Vertex
{
	Position position;
	Color color;

	Vertex();
	Vertex(float x, float y, float z);
	Vertex(float x, float y, float z, float r, float g, float b, float a);
	Vertex(const Position& position);
	Vertex(const Position& position, const Color& color);

	operator float*();
};