#include "Game.h"

#include "Character.h"

Game::Game(int width, int height, const char* title) : BaseGame(width, height, title)
{
	entities.push_back(new Shape(renderer));


	entities.front()->setIsTrigger(true);
	entities.front()->setColor(vec4(0.0f, 0.f, 0.f, 1.f));
	entities.front()->transform.setScale(vec3(width, height, 0.f));

	/*Character* background = new Character(renderer, false, false);
	background->setIsTrigger(true);
	background->loadTexture("../res/textures/fondo.jpg");
	background->transform.setScale(vec3(800, 600, 0));
	background->transform.setPos(vec3(0, 0, 0));
	entities.push_back(background);*/

	entities.push_back(new Character(renderer, true, true));

	Sprite* tv = new Sprite(renderer);
	tv->addAnimation(3.f, 5, 9, "../res/textures/sonic.png",
		vec2(0.157f, 0.69f), vec2(0.06f, 0.107f));
	entities.push_back(tv);

	/*Shape* shape = new Shape(renderer);
	shape->setIsTrigger(true);
	shape->setColor(vec4(1.0f, 0.f, 0.f, 1.f));
	shape->transform.setScale(vec3(10, 10, 0.f));
	entities.push_back(shape);*/

}

Game::~Game()
{
}

void Game::update()
{
	float speed = 100.f;
	float camSens = 5.f;

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
}
