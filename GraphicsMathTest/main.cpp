#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Color.h"
#include "Position.h"
#include "Vertex.h"

TEST_CASE("A Color can be converted to an array of floats")
{
	Color color(0.5f, 1.f, 0.3f, 1.f);
	const auto colorComponents = static_cast<float*>(color);
	REQUIRE(colorComponents[0] == 0.5f);
	REQUIRE(colorComponents[1] == 1.f);
	REQUIRE(colorComponents[2] == 0.3f);
	REQUIRE(colorComponents[3] == 1.f);
}

TEST_CASE("A Position can be converted to an array of floats")
{
	Position position(1.f, 2.f, 3.f);
	const auto positionComponents = static_cast<float*>(position);
	REQUIRE(positionComponents[0] == 1.f);
	REQUIRE(positionComponents[1] == 2.f);
	REQUIRE(positionComponents[2] == 3.f);
}

TEST_CASE("A Vertex can be converted to an array of floats")
{
	Vertex vertex(Position(1.f, 2.f, 3.f), Color(0.5f, 1.f, 0.3f, 1.f));
	const auto vertexComponents = static_cast<float*>(vertex);
	REQUIRE(vertexComponents[0] == 1.f);
	REQUIRE(vertexComponents[1] == 2.f);
	REQUIRE(vertexComponents[2] == 3.f);
	REQUIRE(vertexComponents[3] == 0.5f);
	REQUIRE(vertexComponents[4] == 1.f);
	REQUIRE(vertexComponents[5] == 0.3f);
	REQUIRE(vertexComponents[6] == 1.f);
}