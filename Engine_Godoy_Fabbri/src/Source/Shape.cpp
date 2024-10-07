#include "Shape.h"

ToToEng::Shape::Shape(Renderer* renderer) : Entity2D(renderer)
{
	vertexQty = 4;
	indexQty = 6;
	id = 1;

	positions = new float[vertexQty * 3]
	{
		-.5f, -.5f, 0.f,
		.5f, -.5f, 0.f,
		-.5f, .5f, 0.f,
		.5f, .5f, 0.f
	};

	colors = new float[vertexQty * 4]
	{
		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f
	};

	textureCoords = new float[vertexQty * 2]
	{
		0.f, 1.f,
		1.f, 1.f,
		0.f, 0.f,
		1.f, 0.f
	};

	indices = new unsigned int[indexQty]
	{
		0, 1, 2,
		1, 2, 3,
	};

	updateVao();

	collider = new BoxCollider2D({0.f, 0.f}, {1.f, 1.f}, &transform);
}

ToToEng::Shape::~Shape()
{
}

void ToToEng::Shape::draw()
{
	renderer->drawShape(VAO, indexQty, color, transform.getTransformMatrix());
}
