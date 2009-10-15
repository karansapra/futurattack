/*
 * Main.cpp
 *
 *  Created on: 1 oct. 2009
 *      Author: clement
 */

#include <stdio.h>
#include "Game.h"


class MyGameplay : public IGameplay
{
	TestFrame * tf;
public:
	MyGameplay()
	{
		tf = new TestFrame();
		Engine * e = &Engine::GetInstance();
		e->SetCurrentIViewable(*tf);
		e->SetCurrentIKeyboard(*tf);
		e->SetCurrentIMouse(*tf);
	}

	void GameplayProcessing()
	{

	}
};


int main(int argc, char ** argv)
{
	Engine * e = &Engine::GetInstance();
	e->InitAll(&argc,argv);
	e->SetCurrentIGameplay(*new MyGameplay());
	e->Run();
	return 0;
}
