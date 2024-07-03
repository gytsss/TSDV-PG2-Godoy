#pragma once

#include "../src/Headers/BaseGame.h"
#include "Headers/Model.h"

using namespace ToToEng;

class Game :
	public BaseGame
{
public:

	Model* model;
	Game(int width, int height, const char* title);
	~Game() override;

	void update() override;
};