#include "Character.h"

#include "Headers/GameTime.h"
#include "Headers/Input.h"

using namespace ToToEng;

Character::Character(Renderer* renderer, bool hasMovement, bool hasAnimation) : Sprite(renderer)
{
	accel = 20.f;
	vel = vec3(0.f);
	maxSpeed = 4.f;
	friction = .1f;
	this->hasMovement = hasMovement;
	this->hasAnimation = hasAnimation;
	transform.setPos(vec3(0.f, 100.f, 0.f));

	if (hasAnimation)
	{
		addAnimation(1.f, 12, 9, "../res/textures/sonic.png",
			vec2(0.32f, 0.25f), vec2(0.0445f, 0.09f));
		//animation->setAnimByIndex(2);
	}
	else
	{
		loadTexture("../res/textures/fondo.jpg");
	}

}

Character::~Character()
{
}

void Character::update()
{

}

void Character::accelerateInDir(vec3 dir)
{
	vel += dir * accel;

	if (length(vel) > maxSpeed)
		vel = normalize(vel) * maxSpeed;
}
