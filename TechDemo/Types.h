#pragma once

struct Color
{
	static Color Black() { return Color(0.f, 0.f, 0.f, 1.f); }
	static Color Red() { return Color(1.f, 0.f, 0.f, 1.f); }
	static Color Yellow() { return Color(1.f, 1.f, 0.f, 1.f); }
	static Color Green() { return Color(0.f, 1.f, 0.f, 1.f); }
	static Color Cyan() { return Color(0.f, 1.f, 1.f, 1.f); }
	static Color Blue() { return Color(0.f, 0.f, 1.f, 1.f); }
	static Color Magenta() { return Color(1.f, 0.f, 1.f, 1.f); }
	static Color White() { return Color(1.f, 1.f, 1.f, 1.f); }

	Color() :
		r(0.f), g(0.f), b(0.f), a(1.f) {}
	Color(float r, float g, float b, float a) :
		r(r), g(g), b(b), a(a) {}
	Color(const Color& other) :
		r(other.r), g(other.g), b(other.b), a(other.a) {}

	operator float*() { return reinterpret_cast<float*>(this); }
	operator const float*() const { return reinterpret_cast<const float*>(this); }

	float r, g, b, a;
};

struct Position
{
	Position() :
		x(0.f), y(0.f), z(0.f) {}
	Position(float x, float y, float z) :
		x(x), y(y), z(z) {}
	Position(const Position& other) :
		x(other.x), y(other.y), z(other.z) {}

	operator float*() { return reinterpret_cast<float*>(this); }

	float x, y, z;
};

struct Vertex
{
	Vertex() :
		position(0.f, 0.f, 0.f), color(Color::White()) {}
	Vertex(float x, float y, float z) :
		position(x, y, z), color(Color::White()) {}
	Vertex(float x, float y, float z, float r, float g, float b, float a) :
		position(x, y, z), color(r, g, b, a) {}
	Vertex(const Position& position) :
		position(position), color(Color::White()) {}
	Vertex(const Position& position, const Color& color) :
		position(position), color(color) {}

	operator float*() { return reinterpret_cast<float*>(this); }

	Position position;
	Color color;
};