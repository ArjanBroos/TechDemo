#include "Vertex.h"

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
