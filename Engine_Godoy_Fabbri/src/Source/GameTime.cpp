#include "GameTime.h"

#include <glfw3.h>

namespace ToToEng
{
    GameTime* GameTime::instance = nullptr;
    
    GameTime::GameTime()
    {
        if (instance != nullptr && this != instance)
        {
            delete this;
            return;
        }
        
        time = 0.f;
        deltaTime = 0.f;
    }

    GameTime* GameTime::getInstance()
    {
        if (!instance)
            instance = new GameTime();
        
        return instance;
    }

    void GameTime::resetTime()
    {
        getInstance()->time = 0.f;
        getInstance()->deltaTime = 0.f;
    }

    void GameTime::update()
    {
        getInstance()->deltaTime = static_cast<float>(glfwGetTime()) - getInstance()->time;
        getInstance()->time = static_cast<float>(glfwGetTime());
    }

    float GameTime::getTime()
    {
        return getInstance()->time;
    }

    float GameTime::getDelta()
    {
        return getInstance()->deltaTime;
    }
}