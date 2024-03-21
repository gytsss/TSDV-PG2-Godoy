#include "CollisionManager.h"


bool ToToEng::CollisionManager::checkOverlap(const BoxCollider2D* one, const BoxCollider2D* two)
{
    const bool collisionX = one->getUpLeft().x < two->getDownRight().x && two->getUpLeft().x < one->getDownRight().x;
    const bool collisionY = one->getUpLeft().y < two->getDownRight().y && two->getUpLeft().y < one->getDownRight().y;

    return collisionX && collisionY;
}

void ToToEng::CollisionManager::checkCollision(BoxCollider2D* one, BoxCollider2D* two)
{
    if (checkOverlap(one, two))
    {
        one->onCollision(two);
        two->onCollision(one);
    }
}