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
		void updateTransformMatrix();

	public:
		Transform();
		~Transform();

#pragma region GETTERS

		vec3 getPos();
		vec3 getScale();
		vec3 getRot();

		vec3 getPrevPos();
		
		mat4 getTransformMatrix();

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

		void setScale(const vec3& v);
		void setScaleX(float x);
		void setScaleY(float y);
		void setScaleZ(float z);

		void setRot(const vec3& v);
		void rotateX(float x);
		void rotateY(float y);
		void rotateZ(float z);

#pragma endregion
	};
}
