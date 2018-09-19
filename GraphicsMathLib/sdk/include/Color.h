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