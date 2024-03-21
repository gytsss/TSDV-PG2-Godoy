#pragma once
#include "Headers/Shape.h"
#include "Headers/Sprite.h"

class Character :
    public ToToEng::Sprite
{
private:
    float accel;
    vec3 vel;
    float maxSpeed;
    float friction;
    bool hasMovement;
    bool hasAnimation;

public:
    explicit Character(ToToEng::Renderer* renderer, bool hasMovement, bool hasAnimation);
    ~Character() override;

    void update() override;

    void accelerateInDir(vec3 dir);
};
