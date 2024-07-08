#pragma once

#include "../src/Headers/BaseGame.h"
#include "Headers/Model.h"
#include "Headers/Lights/PointLight.h"
#include "Headers/Lights/SpotLight.h"
#include "Headers/Lights/DirLight.h"
#include "Headers/Lights/Light.h"

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