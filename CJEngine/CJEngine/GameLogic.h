/*
 * GameLogic.h
 *
 *  Created on: 27 oct. 2009
 *      Author: Clement
 */

#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_

#include "CJEngine.h"
#include "MenuScene.h"
#include "GameBackground.h"

using namespace CJEngine;

class GameLogic : public IGameLogic {
	enum State {MENU,LOADING,IN_GAME};

	Engine * _engine_instance;
	State _current_state;

	MenuScene * _menu;
	GameBackground * _game_background;

public:
	GameLogic();
	virtual ~GameLogic();

	void RenderPass(float sec_time);
	void EventArrived(Event & evt);
};

#endif /* GAMELOGIC_H_ */
