/*
 * main.cpp
 *
 *  Created on: 27 oct. 2009
 *      Author: Clement
 */


#include <stdio.h>
#include <windows.h>

#include "Engine.h"
#include "GameLogic.h"

using namespace CJEngine;

int main(int argc, char ** argv)
{
	Engine * engine = Engine::GetInstance();
	engine->Init(640,480,"CJ Engine Demo",false);
	engine->ExitOnEscape(false);

	GameLogic logic;
	engine->SetCurrentGameLogic(logic);

	engine->Run();

	return 0;
}
