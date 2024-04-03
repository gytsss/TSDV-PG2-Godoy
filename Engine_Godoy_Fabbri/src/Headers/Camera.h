#pragma once
#include "Transform.h"

class TOTO_API Camera
{
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
	
};