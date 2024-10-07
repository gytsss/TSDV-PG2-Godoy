#pragma once

#include "Exports.h"

namespace ToToEng
{
    class TOTO_API GameTime
    {
    private:
        static GameTime* instance;
        float time;
        float deltaTime;
    
        GameTime();
    public:
    
        static GameTime* getInstance();
        static void resetTime();
        static void update();
        static float getTime();
        static float getDelta();
    };
}