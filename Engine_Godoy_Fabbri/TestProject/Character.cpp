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
	if (!hasAnimation)
		Sprite::setHasAnimation(false);
	else
		Sprite::setHasAnimation(true);
	Sprite::update();

	if (hasMovement)
	{
		if (Input::getKey(Input::a, Input::Repeated))
		{
			accelerateInDir(-transform.right() * GameTime::getDelta());
		}

		if (Input::getKey(Input::d, Input::Repeated))
		{
			accelerateInDir(transform.right() * GameTime::getDelta());
		}

		if (Input::getKey(Input::s, Input::Repeated))
		{
			accelerateInDir(-transform.up() * GameTime::getDelta());
		}
		if (Input::getKey(Input::w, Input::Repeated))
		{
			accelerateInDir(transform.up() * GameTime::getDelta());
		}

		if (Input::getKey(Input::q, Input::Repeated))
		{
			accelerateInDir(transform.forward() * GameTime::getDelta());
		}
		if (Input::getKey(Input::e, Input::Repeated))
		{
			accelerateInDir(-transform.forward() * GameTime::getDelta());
		}

		/*if (Input::getKey(Input::q, Input::Repeated))
			transform.rotateZ(100.f * GameTime::getDelta());
		if (Input::getKey(Input::e, Input::Repeated))
			transform.rotateZ(-100.f * GameTime::getDelta());*/

		// if (Input::getKey(Input::f, Input::Pressed))
		//     animation->setAnimByIndex(animation->getAnimIndex() >= 7 ? 0 : animation->getAnimIndex() + 1);

		transform.setPos(transform.getPos() + vel);

		if (length(vel) > 0)
		{
			vel = normalize(vel) * (length(vel) - friction < 0 ? 0 : length(vel) - friction);
			animation->setPlayAnim(true);
		}
		else
			animation->setPlayAnim(false);
	}

}

void Character::accelerateInDir(vec3 dir)
{
	vel += dir * accel;

	if (length(vel) > maxSpeed)
		vel = normalize(vel) * maxSpeed;
}
