#pragma once
#include "Transform.h"

class TOTO_API Camera
{
protected:
	void updateRot();
public:
	vec3 pos;
	vec3 dir;
	vec3 up;
	vec3 rot;


	Camera();
	~Camera();

	void moveRight(float distance);
	void moveUp(float distance);
	void moveForward(float distance);

	void rotYaw(float value);
	void rotPitch(float value);
	
};