#include "Game.h"

#include "Character.h"
#include "Headers/Model.h"
#include "Headers/Entities/Entity3D.h"

Game::Game(int width, int height, const char* title) : BaseGame(width, height, title)
{
    camera->rot = {0, 0, 0}; // reset rot
    //
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


    entities.push_back(new Model(renderer, "../res/models/backpack.obj", true));
    entities.back()->transform.setScale({1, 1, 1});
    entities.back()->transform.setPos({0, 25, 15});
    entities.back()->setColor({1, 1, 1, 1});

    entities.push_back(new Model(renderer, "../res/models/backpack.obj", true));
    entities.back()->transform.setScale({1, 1, 1});
    entities.back()->transform.setPos({10, 25, 15});
    entities.back()->setColor({1, 1, 1, 1});

    entities.push_back(new Model(renderer, "../res/models/CH_Dummy_HurtV2.fbx", false));
    entities.back()->transform.setScale({0.1, 0.1, 0.1});
    entities.back()->transform.setPos({0, 0, 15});
    entities.back()->setColor({1, 1, 1, 1});

    //renderer->addDirLight(new DirLight({0.5f, 0.5f, 0.5f}, {0.4f, 0.4f, 0.4f}, {0.5f, 0.5f, 0.5f}, {-0.2f, -1.0f, -0.3f}));
    //renderer->addPointLight(new PointLight({10.0f, 10.f, 10.f}, {10.0f, 10.f, 10.f}, {10.0f, 10.f, 10.f}, {0.0f, 0.0f, 3.0f}, 1.0f, 0.09f, 0.032f));
    //renderer->addSpotLight(new SpotLight({0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {camera->pos.x, camera->pos.y, camera->pos.z},{camera->pos.x, camera->pos.y, camera->pos.z}, 1.0f, 0.09f, 0.032f, 45.0f, 45.0f));
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
        entities.back()->transform.setPos({
            entities.back()->transform.getPos().x + 5 * GameTime::getDelta(), entities.back()->transform.getPos().y,
            entities.back()->transform.getPos().z
        });
    if (Input::getKey(Input::j, Input::Repeated))
        entities.back()->transform.setPos({
            entities.back()->transform.getPos().x - 5 * GameTime::getDelta(), entities.back()->transform.getPos().y,
            entities.back()->transform.getPos().z
        });

    if (Input::getKey(Input::i, Input::Repeated))
        entities.back()->transform.setPos({
            entities.back()->transform.getPos().x, entities.back()->transform.getPos().y + 5 * GameTime::getDelta(),
            entities.back()->transform.getPos().z
        });
    if (Input::getKey(Input::k, Input::Repeated))
        entities.back()->transform.setPos({
            entities.back()->transform.getPos().x, entities.back()->transform.getPos().y - 5 * GameTime::getDelta(),
            entities.back()->transform.getPos().z
        });


    camera->rotPitch(Input::getMouseDelta().y * camSens);
    camera->rotYaw(Input::getMouseDelta().x * camSens);

    Input::resetMouseDelta();

    if (camera->rot.x > 89.99f)
        camera->rot.x = 89.99f;
    if (camera->rot.x < -89.99f)
        camera->rot.x = -89.99f;

    //model->draw();
}
