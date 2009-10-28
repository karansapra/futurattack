/*
 * GameLogic.cpp
 *
 *  Created on: 27 oct. 2009
 *      Author: Clement
 */

#include "GameLogic.h"

namespace CJEngine {

	GameLogic::GameLogic() {
		_engine_instance = Engine::GetInstance();
		_engine_instance->AddEventReceiver(*this);
	}

	GameLogic::~GameLogic() {

	}

    void GameLogic::ProcessLogic(float sec_time)
    {

    }

    void GameLogic::EventArrived(Event & evt)
    {
    	if (evt.event_type==MOUSE_LEFT_CLICK)
    	{
    		MessageBox(NULL,"TITL!!!!","Clic!",MB_OK);
    	}
    }
}
