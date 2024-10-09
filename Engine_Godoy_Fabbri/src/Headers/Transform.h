#pragma once

#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>

#include "Exports.h"

using namespace glm;

namespace ToToEng
{
	class TOTO_API Transform
	{
	private:
		vec3 pos;
		vec3 scale;
		vec3 rot;

		vec3 prevPos;

		mat4 transformMatrix;

		mat4 posMat;
		mat4 scaleMat;
		mat4 rotMat;
		mat4 worldModel;
		mat4 localModel;
		mat4 parentModel;
		void updateTransformMatrix();

	public:
		Transform();
		~Transform();

		void updateLocalTransformMatrix();
		void updateTransformRotation();

#pragma region GETTERS

		vec3 getPos();
		vec3 getScale();
		vec3 getRot();

		vec3 getPrevPos();
		
		mat4 getTransformMatrix();

		mat4 getWorldModel() { return worldModel; };
		mat4 getLocalModel() { return localModel; };
		mat4 getParentModel() { return parentModel; };

		vec3 up();
		vec3 right();
		vec3 forward();

		void lerpPos(vec3 target, float t);
		void lerpPos(vec2 target, float t);
		void lerpPos2D(vec3 target, float t);

#pragma endregion

#pragma region SETTERS
	
		void setPos(const vec3& v);
		void translateX(float x);
		void translateY(float y);
		void translateZ(float z);
		void moveRight(float x);
		void moveUp(float y);
		void moveForward(float z);

		void setScale(const vec3& v);
		void setScaleX(float x);
		void setScaleY(float y);
		void setScaleZ(float z);

		void setRot(const vec3& v);
		void rotateX(float x);
		void rotateY(float y);
		void rotateZ(float z);

		void setForward(vec3 v);
		void setRight(vec3 v);
		void setUp(vec3 v);

		void setWorldModel(mat4 v) { worldModel = v; }
		void setLocalModel(mat4 v) { localModel = v; }
		void setParentModel(mat4 v) { parentModel = v; }

#pragma endregion

		
	};
#pragma region OTHERS
		vec3 static QuatToVec(quat quat, vec3 vec);
		quat static EulerToQuat(vec3 euler);
#pragma endregion
}