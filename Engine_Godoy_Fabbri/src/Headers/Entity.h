#pragma once

#include "Renderer.h"
#include "Exports.h"
#include "Transform.h"

namespace ToToEng
{

	struct Vector2
	{
		float x;
		float y;
	};

	class TOTO_API Entity
	{
	protected:
		Renderer* renderer;
		float* vertices;
		unsigned int* indices;
		unsigned int VBO;
		unsigned int IBO;
		unsigned int VAO;
		unsigned int id;
		unsigned int indexQty;
		unsigned int vertexQty;
		float* positions;
		float* colors;
		float* textureCoords;

		virtual void updateVao();

	public:
		vec4 color;
		bool active;
		bool isTrigger;
		Transform transform;

		Entity(Renderer* renderer);
		virtual ~Entity();
		
		virtual void genBuffers();
		virtual void deleteBuffers();
		virtual void update();
		virtual void draw() = 0;

#pragma region Getters
		vec4 getColor();
		bool getIsTrigger();
#pragma endregion
		
#pragma region  Setters
		void setColor(vec4 color);
		void setIsTrigger(bool isTrigger);
#pragma endregion
	};
}