#pragma once

#include <list>

#include "CollisionManager.h"
#include "Renderer.h"
#include "Shape.h"
#include "Exports.h"
#include "Input.h"
#include "GameTime.h"

namespace ToToEng
{
    class TOTO_API BaseGame
    {
    private:
        Window* window;
        CollisionManager* collisionManager;

    protected:
        Renderer* renderer;
        std::list<Entity*> entities = std::list<Entity*>();
        
        Camera* camera;

    public:
        BaseGame(int width, int height, const char* title);
        virtual ~BaseGame();

        void run();

        virtual void update() = 0;

        void addDirLight(DirLight* dirLight);
        void addPointLight(PointLight* pointLight);
        void addSpotLight(SpotLight* spotLight);

        void turnOnDirLight(int index);
        void turnOffDirLight(int index);
        void turnDirLight(int index);
        void turnOnPointLight(int index);
        void turnOffPointLight(int index);
        void turnPointLight(int index);
        void turnOnSpotLight(int index);
        void turnOffSpotLight(int index);
        void turnSpotLight(int index);

        void changeCameraMode();
        bool getIsThirdPerson();

        void setView(mat4 view);

    };
}
