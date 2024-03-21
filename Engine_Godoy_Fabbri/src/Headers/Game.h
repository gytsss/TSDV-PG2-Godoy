#pragma once

#include "BaseGame.h"

class Game :
	public ToToEng::BaseGame
{
public:
	Game();
	~Game();

	void update() override;
};