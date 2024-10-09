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
		float* normals;

		//Entity* parent;
		//std::vector<Entity*> children;
		//std::vector <vec3> extremos;

		virtual void updateVao();
		void updateVao3D();
		//void setWorldModelWithParentModel(glm::mat4 parentModel);
		//void updateModelMatrix();

	public:
		vec4 color;
		bool active;
		bool isTrigger;
		Transform transform;

		Entity(Renderer* renderer);
		virtual ~Entity();
		
		virtual void genBuffers();
		void genBuffers3D();
		virtual void deleteBuffers();
		virtual void update();
		virtual void draw() = 0;

		//void AddChildren(Entity* children);
		//void UpdateExtremos();
		//void updateAABBWithChildren(Entity* child);
		

#pragma region Getters
		vec4 getColor();
		bool getIsTrigger();
		
		// mat4 getGlobMat();
		// mat4 getGlobMat(Entity* parent);
		//
		// glm::vec3 GetPosGlobalMat();
		// glm::vec3 GetPos(glm::mat4 mat);
		// glm::vec3 GetRot(glm::mat4 mat);
		// glm::vec3 GetScale(glm::mat4 mat);
		//
		// glm::vec3 ToEulerRad(glm::quat rot);
		// glm::quat GetRotationByMatrix(glm::mat4 mat);
		//
		// glm::vec3 NormalizeAngles(glm::vec3 angles);
		// float NormalizeAngle(float angle);
#pragma endregion
		
#pragma region  Setters
		void setColor(vec4 color);
		void setIsTrigger(bool isTrigger);

		// void SetParent(Entity* parent);
		// void setChildren(std::vector<Entity*> children);
		// void setTransformations();

		//void setVolume(aabb* vol) { volume = vol; }
#pragma endregion
	};
}