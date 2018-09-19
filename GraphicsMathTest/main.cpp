#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Color.h"
#include "Position.h"
#include "Vertex.h"
#include "Vector.h"

TEST_CASE("A Color can be converted to an array of floats")
{
	Color color(0.5f, 1.f, 0.3f, 1.f);
	const auto colorComponents = static_cast<float*>(color);
	CHECK(colorComponents[0] == 0.5f);
	CHECK(colorComponents[1] == 1.f);
	CHECK(colorComponents[2] == 0.3f);
	CHECK(colorComponents[3] == 1.f);
}

TEST_CASE("A Position can be converted to an array of floats")
{
	Position position(1.f, 2.f, 3.f);
	const auto positionComponents = static_cast<float*>(position);
	CHECK(positionComponents[0] == 1.f);
	CHECK(positionComponents[1] == 2.f);
	CHECK(positionComponents[2] == 3.f);
}

TEST_CASE("A Vertex can be converted to an array of floats")
{
	Vertex vertex(Position(1.f, 2.f, 3.f), Color(0.5f, 1.f, 0.3f, 1.f));
	const auto vertexComponents = static_cast<float*>(vertex);
	CHECK(vertexComponents[0] == 1.f);
	CHECK(vertexComponents[1] == 2.f);
	CHECK(vertexComponents[2] == 3.f);
	CHECK(vertexComponents[3] == 0.5f);
	CHECK(vertexComponents[4] == 1.f);
	CHECK(vertexComponents[5] == 0.3f);
	CHECK(vertexComponents[6] == 1.f);
}

TEST_CASE("A Vector can be converted to an array of floats")
{
	Vector vector(1.f, 0.f, 0.f, 1.f);
	const auto vectorComponents = static_cast<float*>(vector);
	CHECK(vectorComponents[0] == 1.f);
	CHECK(vectorComponents[1] == 0.f);
	CHECK(vectorComponents[2] == 0.f);
	CHECK(vectorComponents[3] == 1.f);
}

TEST_CASE("The dot product of (1, 2, 3) and (2, 3, 4) is 20")
{
	const auto dotProduct = Dot(Vector(1.f, 2.f, 3.f), Vector(2.f, 3.f, 4.f));
	REQUIRE(dotProduct == Approx(20.f));
}

TEST_CASE("The cross product of (1, 0, 0) and (0, 1, 0) is (0, 0, 1)")
{
	const auto crossProduct = Cross(Vector(1.f, 0.f, 0.f), Vector(0.f, 1.f, 0.f));
	REQUIRE(crossProduct == Vector(0.f, 0.f, 1.f));
}

TEST_CASE("The cross product of (0, 1, 0) and (1, 0, 0) is (0, 0, -1)")
{
	const auto crossProduct = Cross(Vector(0.f, 1.f, 0.f), Vector(1.f, 0.f, 0.f));
	REQUIRE(crossProduct == Vector(0.f, 0.f, -1.f));
}