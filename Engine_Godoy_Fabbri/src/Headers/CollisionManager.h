#pragma once
#include "BoxCollider2D.h"

namespace ToToEng
{
    class CollisionManager
    {
    public:
        static bool checkOverlap(const BoxCollider2D* one, const BoxCollider2D* two);
        static void checkCollision(BoxCollider2D* one, BoxCollider2D* two);
    };
}