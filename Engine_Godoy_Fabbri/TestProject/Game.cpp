#include "Game.h"

#include "Character.h"
#include "Headers/Entity3D.h"

Game::Game(int width, int height, const char* title) : BaseGame(width, height, title)
{
    entities.push_back(new Entity3D(renderer));
    entities.back()->transform.setScale({1,1,1});
    entities.back()->transform.setPos({0,0,5});
    entities.back()->setColor({0,1,0,1});
    
    
}

Game::~Game()
{
}

void Game::update()
{
    float speed = 1.f;
    float camSens = 0.3f;

    if (Input::getKey(Input::a, Input::Repeated))
        camera->moveRight(-speed * GameTime::getDelta());
    if (Input::getKey(Input::d, Input::Repeated))
        camera->moveRight(speed * GameTime::getDelta());

    if (Input::getKey(Input::w, Input::Repeated))
        camera->moveForward(speed * GameTime::getDelta());
    if (Input::getKey(Input::s, Input::Repeated))
        camera->moveForward(-speed * GameTime::getDelta());

    if (Input::getKey(Input::e, Input::Repeated))
        camera->moveUp(speed * GameTime::getDelta());
    if (Input::getKey(Input::q, Input::Repeated))
        camera->moveUp(-speed * GameTime::getDelta());

    if (Input::getKey(Input::l, Input::Repeated))
        camera->rotYaw(speed * GameTime::getDelta());
    if (Input::getKey(Input::j, Input::Repeated))
        camera->rotYaw(-speed * GameTime::getDelta());

    if (Input::getKey(Input::i, Input::Repeated))
        camera->rotPitch(speed * GameTime::getDelta());
    if (Input::getKey(Input::k, Input::Repeated))
        camera->rotPitch(-speed * GameTime::getDelta());

    camera->rotPitch(Input::getMouseDelta().y * camSens);
    camera->rotYaw(Input::getMouseDelta().x * camSens);

    Input::resetMouseDelta();
    
    if (camera->rot.x > 89.99f)
        camera->rot.x = 89.99f;
    if (camera->rot.x < -89.99f)
        camera->rot.x = -89.99f;
}
