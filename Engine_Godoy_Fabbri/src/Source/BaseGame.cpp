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

        camera->transform.setPos({0, 300, 600});

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
            renderer->setView(lookAt(camera->transform.getPos(),
                                     camera->transform.getPos() + camera->transform.forward(), camera->transform.up()));

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

                    if (!entityOne->isTrigger && !entityTwo->isTrigger)
                    {
                        BoxCollider2D* colliderOne = dynamic_cast<Entity2D*>(entityOne)->collider;
                        BoxCollider2D* colliderTwo = dynamic_cast<Entity2D*>(entityTwo)->collider;

                        if (colliderOne && colliderTwo)
                            CollisionManager::checkCollision(colliderOne, colliderTwo);
                    }
                }
            }

            renderer->beginDraw();

            for (Entity* entity : entities)
                entity->draw();

            renderer->endDraw();

            glfwPollEvents();
        }
    }
}
