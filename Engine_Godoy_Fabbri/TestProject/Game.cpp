#include "Game.h"

#include "Character.h"
#include "Headers/Model.h"
#include "Headers/Entities/Entity3D.h"

Game::Game(int width, int height, const char* title) : BaseGame(width, height, title)
{
    // entities.push_back(new Entity3D(renderer));
    // entities.back()->transform.setScale({20,20,.5f});
    // entities.back()->transform.setPos({0,0,20});
    // entities.back()->setColor({1,0,0,1});
    
    // entities.push_back(new Entity3D(renderer));
    // entities.back()->transform.setScale({1,1,1});
    // entities.back()->transform.setPos({0,0,10});
    // entities.back()->setColor({1,0,0,1});

    // model = new Model(renderer, "../res/models/backpack.obj", true);
    // model->transform.setScale({100,100,100});
    // model->transform.setPos({0,0,5});
    // model->setColor({1,1,1,1});

    entities.push_back(new Model(renderer, "../res/models/CH_Dummy_HurtV2.fbx", false));
    entities.back()->transform.setScale({0.1,0.1,0.1});
    entities.back()->transform.setPos({0,0,5});
    entities.back()->setColor({1,1,1,1});

    entities.push_back(new Model(renderer, "../res/models/backpack.obj", true));
    entities.back()->transform.setScale({1,1,1});
    entities.back()->transform.setPos({10,0,5});
    entities.back()->setColor({1,1,1,1});
    
}

Game::~Game()
{
}

void Game::update()
{
    float speed = 10.f;
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

    //model->draw();
}
