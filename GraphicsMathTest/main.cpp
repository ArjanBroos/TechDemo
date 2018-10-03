#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Color.h"
#include "Position.h"
#include "Vertex.h"
#include "Vector.h"
#include "Matrix.h"
#include <sstream>

class StringBuilder
{
public:
	template<typename T>
	StringBuilder& operator<<(const T& element) { m_stringstream << element; return *this; }
	operator std::string() { return m_stringstream.str(); }
private:
	std::stringstream m_stringstream;
};

namespace Catch {
	template<>
	struct StringMaker<::Vector> {
		static std::string convert(::Vector const& vector)
		{
			return StringBuilder() << "(" << vector.x << ", " << vector.y
				<< ", " << vector.z << ", " << vector.w << ")";
		}
	};
}

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

TEST_CASE("A vector can be assigned via the subscript operator")
{
	Vector vector(0.f, 0.f, 0.f, 0.f);
	vector[1] = 2.f;
	CHECK(vector[1] == 2.f);
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

TEST_CASE("A Matrix can be converted to an array of floats")
{
	const Matrix matrix({
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f, 
		0.f, 0.f, 0.f, 1.f });
	CHECK(matrix.elements[0] == 1.f);
	CHECK(matrix.elements[1] == 0.f);
	CHECK(matrix.elements[2] == 0.f);
	CHECK(matrix.elements[3] == 0.f);
	CHECK(matrix.elements[4] == 0.f);
	CHECK(matrix.elements[5] == 1.f);
	CHECK(matrix.elements[6] == 0.f);
	CHECK(matrix.elements[7] == 0.f);
	CHECK(matrix.elements[8] == 0.f);
	CHECK(matrix.elements[9] == 0.f);
	CHECK(matrix.elements[10] == 1.f);
	CHECK(matrix.elements[11] == 0.f);
	CHECK(matrix.elements[12] == 0.f);
	CHECK(matrix.elements[13] == 0.f);
	CHECK(matrix.elements[14] == 0.f);
	CHECK(matrix.elements[15] == 1.f);
}

TEST_CASE("The second row of an identity matrix is (0, 1, 0, 0)")
{
	Matrix matrix = Matrix::Identity();
	CHECK(matrix.Row(1) == Vector(0.f, 1.f, 0.f, 0.f));
}

TEST_CASE("A Vector multiplied by an identity Matrix results in the same vector")
{
	const Matrix identity = Matrix::Identity();
	const Vector vector(1.f, 2.f, 3.f);
	const auto multipliedVector = identity * vector;
	CHECK(vector == multipliedVector);
}

TEST_CASE("A Vector multiplied by a translation matrix results in the same vector")
{
	const Matrix translation = Matrix::Translation(1.f, 2.f, 3.f);
	const Vector vector(0.f, 1.f, 2.f, 0.f);
	const auto multipliedVector = translation * vector;
	CHECK(vector == multipliedVector);
}

TEST_CASE("A Point multiplied by a translation matrix results in a translated point")
{
	const Matrix translation = Matrix::Translation(1.f, 2.f, 3.f);
	const Vector point(0.f, 1.f, 2.f, 1.f);
	const auto multipliedPoint = translation * point;
	const Vector expectedPoint(1.f, 3.f, 5.f, 1.f);
	CHECK(multipliedPoint == expectedPoint);
}

TEST_CASE("A Vector multiplied by a scaling matrix results in a scaled vector")
{
	const Matrix scaling = Matrix::Scaling(1.f, 2.f, 3.f);
	const Vector vector(1.f, 2.f, 4.f);
	const Vector scaledVector = scaling * vector;
	const Vector expectedVector(1.f, 4.f, 12.f);
	CHECK(scaledVector == expectedVector);
}

TEST_CASE("A Vector multiplied by a rotation matrix results in a rotated vector")
{
	const Matrix rotation = Matrix::Rotation(1.f, 2.f, 3.f);
	const Vector vector(1.f, 2.f, 4.f);
	const Vector rotatedVector = rotation * vector;
	const Vector expectedVector(1.f, 4.f, 12.f);
	CHECK(rotatedVector == expectedVector);
}
