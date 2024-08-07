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

	vec3 thirdPersonCameraReference;
	vec3 thirdPersonCameraOffset;
	bool thirdPersonCamera = false;


	Camera();
	~Camera();

	void moveRight(float distance);
	void moveUp(float distance);
	void moveForward(float distance);

	void rotYaw(float value);
	void rotPitch(float value);

	 void updateTpCamera();

	void setCameraReference(vec3 obj);

	void setThirdPersonCamera(bool value);

	vec3 getForward() const;
	vec3 getRight() const;
	vec3 getUp() const;
	bool getIsThirdPerson() const;
	
	
};