#include "BaseGame.h"

#include "CollisionManager.h"
#include "Sprite.h"

namespace ToToEng
{
    BaseGame::BaseGame(int width, int height, const char* title)
    {
        camera = new Camera();
        window = new Window(width, height, title);
        renderer = new Renderer(window, camera);
        collisionManager = new CollisionManager();

        camera->pos = vec3(0, 0, 10);
        //setCameraReference({0, 0, 0});

        GameTime::resetTime();
    }

    BaseGame::~BaseGame()
    {
        delete renderer;
        delete window;
        delete camera;
        delete collisionManager;

        for (int i = 0; i < static_cast<int>(entities.size()); i++)
        {
            const Entity* tmp = entities.front();
            entities.pop_front();
            delete tmp;
        }


        entities.clear();
    }

    void BaseGame::run()
    {
        while (!window->shouldClose())
        {
            GameTime::update();
            if (camera->thirdPersonCamera)
            {
                camera->pos = (entities.front()->transform.getPos() - (entities.front()->transform.forward() * - 30.0f));
                camera->dir = entities.front()->transform.getPos();
                renderer->setView(lookAt(camera->pos, camera->thirdPersonCameraReference, camera->up));
                camera->updateTpCamera();
            }
            else
                renderer->setView(lookAt(camera->pos, camera->pos + camera->dir, camera->up));

            for (Entity* entity : entities)
                entity->update();
            update();

            for (Entity* entityOne : entities)
            {
                bool newCollider = false;

                for (Entity* entityTwo : entities)
                {
                    if (entityOne == entityTwo)
                    {
                        newCollider = true;
                        continue;
                    }

                    if (!newCollider)
                        continue;
                    
                }
            }

            renderer->beginDraw();

            for (Entity* entity : entities)
                entity->draw();

            renderer->endDraw();

            glfwPollEvents();
        }
    }

    void BaseGame::addDirLight(DirLight* dirLight)
    {
        renderer->addDirLight(dirLight);
    }

    void BaseGame::addPointLight(PointLight* pointLight)
    {
        renderer->addPointLight(pointLight);
    }

    void BaseGame::addSpotLight(SpotLight* spotLight)
    {
        renderer->addSpotLight(spotLight);
    }

    void BaseGame::turnOnDirLight(int index)
    {
        renderer->turnOnDirLight(index);
    }

    void BaseGame::turnOffDirLight(int index)
    {
        renderer->turnOffDirLight(index);
    }

    void BaseGame::turnDirLight(int index)
    {
        renderer->turnDirLight(index);
    }

    void BaseGame::turnPointLight(int index)
    {
        renderer->turnPointLight(index);
    }

    void BaseGame::turnSpotLight(int index)
    {
        renderer->turnSpotLight(index);
    }

    void BaseGame::turnOnPointLight(int index)
    {
        renderer->turnOnPointLight(index);
    }

    void BaseGame::turnOffPointLight(int index)
    {
        renderer->turnOffPointLight(index);
    }

    void BaseGame::turnOnSpotLight(int index)
    {
        renderer->turnOnSpotLight(index);
    }

    void BaseGame::turnOffSpotLight(int index)
    {
        renderer->turnOffSpotLight(index);
    }

    void BaseGame::changeCameraMode()
    {
        renderer->changeCameraMode();
    }

    bool BaseGame::getIsThirdPerson()
    {
        return renderer->getIsThirdPerson();
    }

    void BaseGame::setView(mat4 view)
    {
        renderer->setView(view);
    }
}
