#pragma once

struct Color
{
	float r, g, b, a;

	Color();
	Color(float r, float g, float b, float a);
	Color(const Color& other);

	operator float*();
	operator const float*() const;

	static Color Black();
	static Color Red();
	static Color Yellow();
	static Color Green();
	static Color Cyan();
	static Color Blue();
	static Color Magenta();
	static Color White();
};

struct Position
{
	float x, y, z;

	Position();
	Position(float x, float y, float z);
	Position(const Position& other);

	operator float*();
};

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