#include "Types.h"

Color::Color() :
	r(0.f), g(0.f), b(0.f), a(1.f) {}
Color::Color(float r, float g, float b, float a) :
	r(r), g(g), b(b), a(a) {}
Color::Color(const Color& other) :
	r(other.r), g(other.g), b(other.b), a(other.a) {}

Color::operator float*()
{ 
	return reinterpret_cast<float*>(this);
}

Color::operator const float*() const
{ 
	return reinterpret_cast<const float*>(this);
}

Color Color::Black() { 
	return Color(0.f, 0.f, 0.f, 1.f);
}

Color Color::Red() { 
	return Color(1.f, 0.f, 0.f, 1.f); 
}

Color Color::Yellow() { 
	return Color(1.f, 1.f, 0.f, 1.f); 
}

Color Color::Green() { 
	return Color(0.f, 1.f, 0.f, 1.f); 
}

Color Color::Cyan()
{ 
	return Color(0.f, 1.f, 1.f, 1.f);
}

Color Color::Blue()
{ 
	return Color(0.f, 0.f, 1.f, 1.f); 
}

Color Color::Magenta() 
{
	return Color(1.f, 0.f, 1.f, 1.f); 
}

Color Color::White() 
{ 
	return Color(1.f, 1.f, 1.f, 1.f);
}

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

Vertex::Vertex() : 
	position(0.f, 0.f, 0.f), color(Color::White()) {}
Vertex::Vertex(float x, float y, float z) :	
	position(x, y, z), color(Color::White()) {}
Vertex::Vertex(float x, float y, float z, float r, float g, float b, float a) :
	position(x, y, z), color(r, g, b, a) {}
Vertex::Vertex(const Position& position) : 
	position(position), color(Color::White()) {}
Vertex::Vertex(const Position& position, const Color& color) :
	position(position), color(color) {}

Vertex::operator float*() 
{ 
	return reinterpret_cast<float*>(this);
}
