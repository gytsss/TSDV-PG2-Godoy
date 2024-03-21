#pragma once

#include "../src/Headers/BaseGame.h"

using namespace ToToEng;

class Game :
	public BaseGame
{
public:
	Game(int width, int height, const char* title);
	~Game() override;

	void update() override;
};