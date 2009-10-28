/*
 * Engine.h
 *
 *  Created on: 27 oct. 2009
 *      Author: Clement
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <vector>
#include <math.h>

#include "IEventReceiver.h"
#include "IScene.h"
#include "IGameLogic.h"

namespace CJEngine {

using namespace std;

typedef vector<IEventReceiver*>::iterator IEventReceiverPtrIterator;

class Engine {
	Engine();

	//To adjust the pixel format correctly
	void _SetDCPixelFormat(HDC hdc);

	void _GLRender();
	void _GLInit();


	//Holds the unique instance of the engine
	static Engine * _engine_instance;

	//Parameters of the engine
	int _width, _height;
	char *_title;
	bool _fullscreen;
	float _time;
	float _fps;
	LARGE_INTEGER _t0;
	float _cpu_frequency;

	bool _quit_on_escape;

	//Windows parameters
	HINSTANCE _hinstance;
	HWND _mainframe;
	HDC _hdc;
	HGLRC _hglrc;

	//To keep trace of IEventReceiver's
	vector<IEventReceiver*> _ieventreceivers;

	IScene * _iscene;
	IGameLogic * _igamelogic;

public:
	virtual ~Engine();

	//To obtain the unique instance
	static Engine * GetInstance();
	//Call it at the start of the main
	bool Init(int width, int height, const char * title, bool fullscreen);
	//Call it when you have finished config.
	void Run();


	//Get the time since the engine started
	float GetSecondsElapsed();
	//Retrieve the FPS framerate
	float GetFPS();

	//Change the title of the window
	void SetTitle(char * title);
	void ExitOnEscape(bool enabled);

	//Add a new listener for the events
	void AddEventReceiver(const IEventReceiver & ieventreceiver);
	void RemoveEventReceiver(const IEventReceiver & ieventreceiver);

	//Manage scene rendering
	void SetCurrentScene(const IScene & scene);
	void RemoveCurrentScene();

	//Manage Game logic
	void SetCurrentGameLogic(const IGameLogic & logic);
	void RemoveCurrentGameLogic();

	//Window processing DONT USE IT!!!
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
};

//Wrapper for the windows processing function
LRESULT CALLBACK _wnd_proc_wrapper(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

}

#endif /* ENGINE_H_ */
