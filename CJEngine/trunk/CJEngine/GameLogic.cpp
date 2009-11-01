/*
 * GameLogic.cpp
 *
 *  Created on: 27 oct. 2009
 *      Author: Clement
 */

#include "GameLogic.h"

GameLogic::GameLogic() {
	_current_state = MENU;
	_engine_instance = Engine::GetInstance();

	_menu = new MenuScene();
}

GameLogic::~GameLogic() {

}

void GameLogic::RenderPass(float sec_time)
{
	switch (_current_state)
	{
	case MENU:
		_engine_instance->DrawScene(*_menu);
		break;

	case IN_GAME:
		_engine_instance->DrawScene(*_game_background);
		if (_engine_instance->IsKeyPressed(VK_UP))
			_game_background->Move(0.0,-20.0);
		if (_engine_instance->IsKeyPressed(VK_DOWN))
			_game_background->Move(0.0,20.0);
		if (_engine_instance->IsKeyPressed(VK_LEFT))
			_game_background->Move(-20.0,0.0);
		if (_engine_instance->IsKeyPressed(VK_RIGHT))
			_game_background->Move(20.0,0.0);
		break;

	default:
		break;
	}
}

void GameLogic::EventArrived(Event & evt)
{
	if (evt.event_type == MOUSE_LEFT_CLICK && _current_state==IN_GAME)
	{
		_game_background->take_photo = true;
		_game_background->SelectionMode(evt.mousex,evt.mousey);
	}
	if (evt.event_type == KEYDOWN)
	{
		if (evt.keycode==0x41 && _menu!=0)
		{
			_game_background = new GameBackground();
			_current_state=IN_GAME;
			delete _menu;
			_menu = 0;
		} else if (evt.keycode==VK_SPACE && _current_state==IN_GAME)
		{
			_game_background->switch_cam = !_game_background->switch_cam;
		} else if (evt.keycode==0x43 && _current_state==IN_GAME)
		{
			
		}
	}
}
