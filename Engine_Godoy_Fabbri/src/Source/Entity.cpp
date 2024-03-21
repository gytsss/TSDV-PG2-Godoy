#include "Entity.h"

namespace ToToEng
{
	Entity::Entity(Renderer* renderer)
	{
		this->renderer = renderer;

		isTrigger = false;

		color = { 1, 1, 1, 1 };

		vertices = new float();

		transform = Transform();
	}

	Entity::~Entity()
	{
		delete positions;
		delete colors;
		delete vertices;
		delete indices;

		Entity::deleteBuffers();
	}

	void Entity::genBuffers()
	{
		renderer->genVertexBuffer(VBO, VAO, vertices, id, vertexQty);
		renderer->genIndexBuffer(IBO, indices, id, indexQty);
	}

	void Entity::deleteBuffers()
	{
		renderer->deleteBuffers(VBO, IBO, VAO, id);
	}

	void Entity::update()
	{
	}

	void Entity::setColor(vec4 color)
	{
		this->color = color;
	}

	void Entity::setIsTrigger(bool isTrigger)
	{
		this->isTrigger = isTrigger;
	}

	vec4 Entity::getColor()
	{
		return color;
	}

	bool Entity::getIsTrigger()
	{
		return isTrigger;
	}

	void Entity::updateVao()
	{
		delete vertices;

		vertices = new float[vertexQty * 9];

		for (unsigned int i = 0; i < vertexQty; i++)
		{
			vertices[9 * i] = positions[i * 3];
			vertices[9 * i + 1] = positions[i * 3 + 1];
			vertices[9 * i + 2] = positions[i * 3 + 2];

			vertices[9 * i + 3] = colors[i * 4];
			vertices[9 * i + 4] = colors[i * 4 + 1];
			vertices[9 * i + 5] = colors[i * 4 + 2];
			vertices[9 * i + 6] = colors[i * 4 + 3];

			vertices[9 * i + 7] = textureCoords[i * 2];
			vertices[9 * i + 8] = textureCoords[i * 2 + 1];
		}

		genBuffers();
	}
}