#include "Entity.h"

namespace ToToEng
{
	Entity::Entity(Renderer* renderer)
	{
		this->renderer = renderer;

		isTrigger = false;

		color = { 0, 1, 0, 1 };

		vertices = new float();

		transform = Transform();
	}

	Entity::~Entity()
	{
		delete positions;
		delete colors;
		delete vertices;
		delete indices;
		delete normals;

		Entity::deleteBuffers();
	}

	void Entity::genBuffers()
	{
		renderer->genVertexBuffer(VBO, VAO, vertices, id, vertexQty);
		renderer->genIndexBuffer(IBO, indices, id, indexQty);
	}
	void Entity::genBuffers3D()
	{
		renderer->genVertexBuffer3D(VBO, VAO, vertices, id, vertexQty);
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

		int positionSize = 3;
		int colorsSize = 4;
		int textureCoordsSize = 2;
		
		for (unsigned int i = 0; i < vertexQty; i++)
		{
			
			vertices[9 * i] = positions[i * positionSize];
			vertices[9 * i + 1] = positions[i * positionSize + 1];
			vertices[9 * i + 2] = positions[i * positionSize + 2];

			vertices[9 * i + 3] = colors[i * colorsSize];
			vertices[9 * i + 4] = colors[i * colorsSize + 1];
			vertices[9 * i + 5] = colors[i * colorsSize + 2];
			vertices[9 * i + 6] = colors[i * colorsSize + positionSize];

			vertices[9 * i + 7] = textureCoords[i * textureCoordsSize];
			vertices[9 * i + 8] = textureCoords[i * textureCoordsSize + 1];
		}

		
		genBuffers();
	}
	void Entity::updateVao3D()
	{
		delete vertices;

		vertices = new float[vertexQty * 12];

		int positionSize = 3;
		int colorsSize = 4;
		int textureCoordsSize = 2;
		int normalsSize = 3;

		for (unsigned int i = 0; i < vertexQty; i++)
		{
			vertices[12 * i] = positions[i * positionSize];
			vertices[12 * i + 1] = positions[i * positionSize + 1];
			vertices[12 * i + 2] = positions[i * positionSize + 2];

			vertices[12 * i + 3] = colors[i * colorsSize];
			vertices[12 * i + 4] = colors[i * colorsSize + 1];
			vertices[12 * i + 5] = colors[i * colorsSize + 2];
			vertices[12 * i + 6] = colors[i * colorsSize + positionSize];

			vertices[12 * i + 7] = textureCoords[i * textureCoordsSize];
			vertices[12 * i + 8] = textureCoords[i * textureCoordsSize + 1];

			vertices[12 * i + 9] = normals[i * normalsSize];
			vertices[12 * i + 10] = normals[i * normalsSize + 1];
			vertices[12 * i + 11] = normals[i * normalsSize + 2];
		}

		genBuffers3D();
	}
}