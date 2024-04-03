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

void Camera::updateRot()
{
	dir.x = cos(glm::radians(rot.y)) * cos(glm::radians(rot.x));
	dir.y = sin(glm::radians(rot.x));
	dir.z = sin(glm::radians(rot.y)) * cos(glm::radians(rot.x));
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

void Camera::rotYaw(float value)
{
	rot.y += value;

	if (rot.y > 360.0f)
		rot.y -= 360.0f;
	else if (rot.y < 0.0f)
		rot.y += 360.0f;

	updateRot();
}

void Camera::rotPitch(float value)
{
	rot.x += value;

	rot.x = clamp(rot.x, -89.99f, 89.99f);

	updateRot();
}
