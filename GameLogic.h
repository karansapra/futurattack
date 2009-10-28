/*
 * GameLogic.h
 *
 *  Created on: 27 oct. 2009
 *      Author: Clement
 */

#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_

#include <windows.h>
#include "Engine.h"
#include "IGameLogic.h"
#include "IEventReceiver.h"

namespace CJEngine {

class GameLogic : public IGameLogic, public IEventReceiver{
	Engine * _engine_instance;

public:
	GameLogic();
	virtual ~GameLogic();

	void ProcessLogic(float sec_time);
	void EventArrived(Event & evt);
};

}

#endif /* GAMELOGIC_H_ */
