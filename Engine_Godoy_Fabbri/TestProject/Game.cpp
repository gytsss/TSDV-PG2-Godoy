#include "Game.h"

#include "Character.h"
#include "Headers/Model.h"
#include "Headers/Entities/Entity3D.h"
#include "Headers/Lights/PointLight.h"
#include "Headers/Renderer.h"


Game::Game(int width, int height, const char* title) : BaseGame(width, height, title)
{
    camera->dir = {0, 0, 0};

    entities.push_back(new Model(renderer, "../res/models/backpack.obj", true));
    entities.back()->transform.setScale({1, 1, 1});
    entities.back()->transform.setPos({0, 0, 0});
    entities.back()->setColor({1, 1, 1, 1});

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

    //addDirLight(new DirLight({0.5f, 0.5f, 0.5f}, {0.4f, 0.4f, 0.4f}, {0.5f, 0.5f, 0.5f}, {-0.2f, -1.0f, -0.3f}));
    //addPointLight(new PointLight({1.0f, 1.f, 1.f}, {10.0f, 10.f, 10.f}, {10.0f, 10.f, 10.f}, {0.0f, 0.0f, 20.0f}, 1.0f, 0.09f, 0.032f));
    addSpotLight(new SpotLight({0.0f, 0.0f, 0.0f}, {10.0f, 10.0f, 10.0f}, {10.0f, 10.0f, 10.0f}, {10, 25, 15},
                               {0, -1, 0}, 1.0f, 0.09f, 0.032f, glm::cos(glm::radians(10.5f)),
                               glm::cos(glm::radians(10.5f))));
    addSpotLight(new SpotLight({0.0f, 0.0f, 0.0f}, {10.0f, 10.0f, 10.0f}, {10.0f, 10.0f, 10.0f}, {-10, 25, 15},{0, -1, 0}, 1.0f, 0.09f, 0.032f, glm::cos(glm::radians(10.5f)), glm::cos(glm::radians(10.5f))));
}

Game::~Game()
{
}

void Game::update()
{
    float speed = 10.f;
    float camSens = 0.3f;

    if (!getIsThirdPerson())
    {
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
    }
    else
    {
        if (Input::getKey(Input::a, Input::Repeated))
            entities.front()->transform.moveRight(speed * GameTime::getDelta());

        if (Input::getKey(Input::d, Input::Repeated))
            entities.front()->transform.moveRight(-speed * GameTime::getDelta());

        if (Input::getKey(Input::w, Input::Repeated))
            entities.front()->transform.moveForward(-speed * GameTime::getDelta());
        if (Input::getKey(Input::s, Input::Repeated))
            entities.front()->transform.moveForward(speed * GameTime::getDelta());

        if (Input::getKey(Input::e, Input::Repeated))
            entities.front()->transform.moveUp(speed * GameTime::getDelta());
        if (Input::getKey(Input::q, Input::Repeated))
            entities.front()->transform.moveUp(-speed * GameTime::getDelta());


        entities.front()->transform.rotateY(-Input::getMouseDelta().x * camSens);
        entities.front()->transform.rotateX(-Input::getMouseDelta().y * camSens);

        camera->setCameraReference(entities.front()->transform.getPos());
    }

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

    if (Input::getKey(Input::c, Input::Pressed))
        changeCameraMode();
    if (Input::getKey(Input::r, Input::Pressed))
        turnSpotLight(0);

    camera->rotPitch(Input::getMouseDelta().y * camSens);
    camera->rotYaw(Input::getMouseDelta().x * camSens);

    Input::resetMouseDelta();

    if (camera->rot.x > 89.99f)
        camera->rot.x = 89.99f;
    if (camera->rot.x < -77.99f)
        camera->rot.x = -77.99f;
}
