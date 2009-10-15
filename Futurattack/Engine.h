/*
 * Engine.h
 *
 *  Created on: 1 oct. 2009
 *      Author: clement
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include <stdio.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <GL/glx.h>
#include "BaseObject.h"
#include "IViewable.h"
#include "IGameplay.h"
#include "IKeyboard.h"
#include "IMouse.h"


//Pour permettre le rendu des frames
void _display_func();
void _exit_func();

//Pour les IKeyboard
void _kb_func(unsigned char key, int a, int b);

void _mouse_func(int button, int state, int x, int y);



class Engine: public BaseObject {
	Engine();

	//Instance de l'objet en cours
	static Engine * _object;

	bool _init_passed;
	int _resx;
	int _resy;
	float _ms_time;

	IViewable * _iviewable;
	IGameplay * _igameplay;
	IKeyboard * _ikeyboard;
	IMouse * _imouse;

	float _dbg_message_time;
	char _dbg_message[MAX_DBG_MESSAGE_LENGTH];


	/*
	 *
	 * WINDOW MANAGMENT
	 *
	 */
	Display * 		_dpy;
	Window 			_root;
	Window 			_window;
	GLXContext		_glx_context;
	XEvent			_xevent;

public:
	static Engine & GetInstance();

	void InitAll(int * argc, char ** argv,int resx=640, int resy=480, bool double_buffered=true, bool fullscreen=false);
	void Run();

	float GetCurrentTime();
	void ResetCurrentTime();

	void ShowDebugMessage(const char * message);

	void SetCurrentIViewable(IViewable & iviewable);
	void SetCurrentIGameplay(IGameplay & igameplay);
	void SetCurrentIKeyboard(IKeyboard & ikeyboard);
	void SetCurrentIMouse(IMouse & imouse);
	int GetScreenWidth();
	int GetScreenHeight();

	inline void GLDisplay();
	inline void GLKeyboard(char key);
	inline void GLMouse(int button, int state, int x, int y);

	const char * ToString();

	virtual ~Engine();

	bool _run;
};

#endif /* ENGINE_H_ */
