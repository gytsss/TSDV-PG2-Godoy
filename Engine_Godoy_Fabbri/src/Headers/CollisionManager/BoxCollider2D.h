#pragma once
#include "Transform.h"

namespace ToToEng
{
    class BoxCollider2D
    {
    private:
        Transform* transform;
        vec2 pos;
        vec2 size;
        vec2 upLeft;
        vec2 downRight;
    
    public:
        BoxCollider2D(vec2 pos, vec2 size, Transform* transform);

        vec2 getPos(bool colliderOnly = false) const;
        vec2 getSize(bool colliderOnly = false) const;
        vec2 getUpLeft(bool colliderOnly = false) const;
        vec2 getDownRight(bool colliderOnly = false) const;

        void onCollision(BoxCollider2D* other);
    };
}