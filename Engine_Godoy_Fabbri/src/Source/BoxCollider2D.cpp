#include "BoxCollider2D.h"

#include <iostream>

namespace ToToEng
{
    BoxCollider2D::BoxCollider2D(const vec2 pos, const vec2 size, Transform* transform)
    {
        this->pos = pos;
        this->size = size;
        this->transform = transform;

        upLeft = vec2(pos.x - size.x / 2, pos.y + size.y / 2);
        downRight = vec2(pos.x + size.x / 2, pos.y - size.y / 2);
    }

    vec2 BoxCollider2D::getPos(const bool colliderOnly) const
    {
        if (colliderOnly)
            return pos;

        return {transform->getPos().x + pos.x, transform->getPos().y + pos.y};
    }

    vec2 BoxCollider2D::getSize(const bool colliderOnly) const
    {
        if (colliderOnly)
            return size;

        return {transform->getScale().x * size.x, transform->getScale().y * size.y};
    }

    vec2 BoxCollider2D::getUpLeft(bool colliderOnly) const
    {
        if (colliderOnly)
            return upLeft;

        return
        {
            transform->getPos().x + upLeft.x - transform->getScale().x / 2.f,
            transform->getPos().y + upLeft.y - transform->getScale().y / 2.f
        };
    }

    vec2 BoxCollider2D::getDownRight(const bool colliderOnly) const
    {
        if (colliderOnly)
            return downRight;

        return
        {
            transform->getPos().x + downRight.x + transform->getScale().x / 2.f,
            transform->getPos().y + downRight.y + transform->getScale().y / 2.f
        };
    }

    void BoxCollider2D::onCollision(BoxCollider2D* other)
    {
        vec2 dir = transform->getPos() - transform->getPrevPos();

        if (dir.x == 0.f && dir.y == 0.f)
            return;
        
        if (abs(transform->getPrevPos().x - other->getPos().x) > abs(transform->getPrevPos().y - other->getPos().y))
        {
            dir.x = dir.x > 0 ? 1.f : -1.f;

            vec3 pos = transform->getPos();
            vec2 otherPos = other->getPos();
            vec2 size = getSize();
            vec2 otherSize = other->getSize();
            
            transform->setPos(vec3(otherPos.x - dir.x * (size.x / 2.f + otherSize.x / 2.f + 1.f) , pos.y ,
                                    pos.z));
        }
        else
        {
            dir.y = dir.y > 0 ? 1.f : -1.f;

            vec3 pos = transform->getPos();
            vec2 otherPos = other->getPos();
            vec2 size = getSize();
            vec2 otherSize = other->getSize();
            
            transform->setPos(vec3(pos.x, otherPos.y - dir.y * (size.y / 2.f + otherSize.y / 2.f + 1.f),
                                    pos.z));
        }
    }
}
