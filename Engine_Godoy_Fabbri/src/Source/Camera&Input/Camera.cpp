#include "Camera.h"

#include <ios>
#include <iostream>

using namespace ToToEng;


Camera::Camera()
{
	pos = vec3(0.0f, 0.0f, 3.0);
	dir = vec3(0.0f, 0.0f, -1.0f);
	up = vec3(0.0f, 1.0f, 0.0f);
	rot = vec3(0.0f, -90.0f, 0.0f);
	thirdPersonCameraOffset = vec3(0.0f, 5.0f, -30.0f);
	thirdPersonCamera = false;
	thirdPersonCameraReference = vec3(0.0f, 0.0f, 0.0f);
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

void Camera::updateTpCamera()
{
	vec3 camUp = normalize(cross(getRight(), getForward()));
	vec3 newOffset = normalize(getForward()) * thirdPersonCameraOffset.z + camUp * thirdPersonCameraOffset.y + getRight() * thirdPersonCameraOffset.x;
	pos = thirdPersonCameraReference + newOffset;
}

void Camera::setCameraReference(vec3 obj)
{
	thirdPersonCameraReference = obj;
}

void Camera::setThirdPersonCamera(bool value)
{
	thirdPersonCamera = value;
}

vec3 Camera::getForward() const
{
	return dir;
}

vec3 Camera::getRight() const
{
	return normalize(cross(dir, up));
}

vec3 Camera::getUp() const
{
	return up;
}

bool Camera::getIsThirdPerson() const
{
	return thirdPersonCamera;
}
