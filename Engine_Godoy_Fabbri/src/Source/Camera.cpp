#include "Camera.h"

using namespace ToToEng;

Camera::Camera()
{
	pos = vec3(0.0f, 0.0f, 3.0);
	dir = vec3(0.0f, 0.0f, -1.0f);
	up = vec3(0.0f, 1.0f, 0.0f);
	rot = vec3(0.0f, -90.0f, 0.0f);
	
}

Camera::~Camera()
{
}

void Camera::moveRight(float distance)
{
	pos += normalize(cross(dir, up)) * distance;
}

void Camera::moveUp(float distance)
{
	pos.y += distance;
}

void Camera::moveForward(float distance)
{
	pos += dir * distance;
}
