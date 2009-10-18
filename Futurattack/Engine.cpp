/*
 * Engine.cpp
 *
 *  Created on: 1 oct. 2009
 *      Author: clement
 */

#include "Engine.h"

void _display_func()
{
	static Engine * e = &Engine::GetInstance();
	e->GLDisplay();
}

void _kb_func(unsigned char key, int a, int b)
{
	static Engine * e = &Engine::GetInstance();
	e->GLKeyboard(key);
}

void _mouse_func(int button, int state, int x, int y)
{
	static Engine * e = &Engine::GetInstance();
	e->GLMouse(button,state,x,y);
}

void _exit_func()
{
}

//Pour créer le Singleton, on init a NULL, pour le creer lors
//de la 1ere demande
Engine * Engine::_object = NULL;

Engine::Engine() : BaseObject()
{
	_init_passed = false;
	_resx = 0;
	_resy = 0;
	_ms_time = 0.0;
	_iviewable = NULL;
	_igameplay = NULL;
	_ikeyboard = NULL;
	_imouse = NULL;
	_dbg_message_time = 0.0;
	_run = true;
	_event_refresh_passes = 0;
}

void Engine::InitAll(int *argc, char **argv, int resx, int resy,bool fullscreen)
{
	_resx = resx;
	_resy = resy;

	/*
	 * INITIALISATION D'OPENGL
	 */
	GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	XVisualInfo * visual_info;
	Colormap colormap;
	XSetWindowAttributes window_attributes;

	_dpy = XOpenDisplay(0);
	if (_dpy==NULL)
	{
		printf("Can't open X display\n");
		return;
	}

	_root = DefaultRootWindow(_dpy);
	visual_info = glXChooseVisual(_dpy,0,att);
	if (visual_info==NULL)
	{
		printf("Your graphics card is probably unsupported\n");
		return;
	}

	colormap = XCreateColormap(_dpy,_root,visual_info->visual,AllocNone);

	window_attributes.colormap = colormap;
	window_attributes.event_mask = ExposureMask | KeyPressMask | PointerMotionMask | ButtonPressMask;

	_window = XCreateWindow(_dpy,_root,0,0,resx,resy,0,visual_info->depth,InputOutput,visual_info->visual,CWColormap|CWEventMask,&window_attributes);
	XMapWindow(_dpy,_window);

	/*
	 * Prise en charge du mode plein ecran
	 */
	if (fullscreen)
	{
		XEvent xev;
		Atom wm_state = XInternAtom(_dpy, "_NET_WM_STATE", False);
		Atom fullscreen = XInternAtom(_dpy, "_NET_WM_STATE_FULLSCREEN", False);

		memset(&xev, 0, sizeof(xev));
		xev.type = ClientMessage;
		xev.xclient.window = _window;
		xev.xclient.message_type = wm_state;
		xev.xclient.format = 32;
		xev.xclient.data.l[0] = 1;
		xev.xclient.data.l[1] = fullscreen;
		xev.xclient.data.l[2] = 0;

		XSendEvent(_dpy, _root, False,SubstructureNotifyMask, &xev);
	}

	XStoreName(_dpy,_window,"Futurattack - RJ Game Studio - 2009");
	_glx_context = glXCreateContext(_dpy,visual_info,NULL,GL_TRUE);
	glXMakeCurrent(_dpy,_window,_glx_context);

	glClearColor(0.0,0.0,0.0,1.0);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_BACK,GL_FILL);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	_init_passed = true;
}

void Engine::Run()
{
	if (!_init_passed)
	{
		printf("Pass [Engine::InitAll] not done --> Exiting\n");
		return;
	}

	while (_run)
	{
		usleep(1000*ENGINE_STEP);
		if (_event_refresh_passes%EVENT_REFRESH_STEP)
		{
			if (true == XCheckMaskEvent(_dpy,KeyPressMask | ButtonPressMask,&_xevent))
			{
				switch (_xevent.type)
				{
				case KeyPress:
					_kb_func(_xevent.xkey.keycode,0,0);
					break;

				case ButtonPress:
					_mouse_func(_xevent.xbutton.button,0,_xevent.xbutton.x,_xevent.xbutton.y);
					break;

				default:
					break;
				}

			}
			_event_refresh_passes = 0;
		} else
			_event_refresh_passes++;

		_ms_time += (float)ENGINE_STEP;

		//Effectue tous les calculs et changements de scene du gameplay, s'il existe
		if (_igameplay!=NULL)
			_igameplay->GameplayProcessing();

		if (_dbg_message_time>0.0)
			_dbg_message_time -= (float)ENGINE_STEP;

		_display_func();
		glXSwapBuffers(_dpy,_window);
	}
}

inline void Engine::GLDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (_iviewable!=NULL)
	{
		_iviewable->PreRender();
		if (_iviewable->GetCamera().HasChanged())
			_iviewable->GetCamera().ApplyChanges();
		_iviewable->Render();
	}

	float _posy_dbg=50.0;
	if (_dbg_message_time>DBG_TIME-500.0)
	{
		_posy_dbg = 50.0*(DBG_TIME-_dbg_message_time)/500.0;
	} else if (_dbg_message_time<=DBG_TIME-500.0 && _dbg_message_time>=500.0)
	{
		_posy_dbg = 50.0;
	} else if (_dbg_message_time<500.0 && _dbg_message_time>0.0)
	{
		_posy_dbg = 50.0-50.0*(500.0-_dbg_message_time)/500.0;
	}

	if (_dbg_message_time>0.0)
	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();

			glLoadIdentity();
			glOrtho(0.0,_resx,_resy,0.0,0.0001,1000.0);
			gluLookAt(0.0,0.0,10.0 ,0.0,0.0,0.0,0.0,1.0,0.0);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

		    glDisable(GL_TEXTURE_2D);
		    glDisable(GL_DEPTH_TEST);
		    glDisable(GL_LIGHTING);
			glEnable(GL_BLEND);

			glBegin(GL_QUADS);
				glColor4f(0.6,0.6,0.6,0.5);
				glVertex3f(0.0,0.0,0.0);
				glVertex3f(0.0,_posy_dbg,0.0);
				glVertex3f(_resx,_posy_dbg,0.0);
				glVertex3f(_resx,0.0,0.0);
			glEnd();
			glColor4f(1.0,1.0,1.0,1.0);
			glRasterPos2f(10.0, _posy_dbg-30.0);

			//glutBitmapString(GLUT_BITMAP_HELVETICA_12,(const unsigned char *)_dbg_message);

			glEnable(GL_TEXTURE_2D);
		    glEnable(GL_DEPTH_TEST);
		    glEnable(GL_LIGHTING);
			glDisable(GL_BLEND);

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	//---------------

}

void Engine::SetCurrentIViewable(IViewable & iviewable)
{
	_iviewable = &iviewable;
}

float Engine::GetCurrentTime()
{
	return _ms_time;
}

void Engine::ResetCurrentTime()
{
	_ms_time = 0.0;
}

void Engine::ShowDebugMessage(const char * message)
{
	_dbg_message_time = DBG_TIME;
	strcpy(_dbg_message,message);
}

int Engine::GetScreenHeight()
{
	return _resy;
}

int Engine::GetScreenWidth()
{
	return _resx;
}

void Engine::SetCurrentIGameplay(IGameplay & igameplay)
{
	_igameplay = &igameplay;
}

void Engine::SetCurrentIKeyboard(IKeyboard & ikeyboard)
{
	_ikeyboard = &ikeyboard;
}

inline void Engine::GLKeyboard(char key)
{
	if (_ikeyboard!=NULL)
		_ikeyboard->KeyPressed(key);
}

inline void Engine::GLMouse(int button, int state, int x, int y)
{
	if (_imouse!=NULL)
		_imouse->ButtonPressed(button,x,y);
}

void Engine::SetCurrentIMouse(IMouse & imouse)
{
	_imouse = &imouse;
}

Engine::~Engine()
{

}

Engine & Engine::GetInstance()
{
	if (_object==NULL)
		_object = new Engine();

	return *_object;
}

const char *Engine::ToString()
{
	return "Engine";
}




