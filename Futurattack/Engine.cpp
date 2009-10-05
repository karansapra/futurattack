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

void _timer_func(int id)
{
	static Engine * e = &Engine::GetInstance();
	e->GLTimer();
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
}

void Engine::InitAll(int *argc, char **argv, int resx, int resy, bool double_buffered, bool fullscreen)
{
	_resx = resx;
	_resy = resy;

	/*
	 * INITIALISATION D'OPENGL
	 */
	glutInit(argc, argv);
	if (double_buffered)
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	else
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(resx,resy);
	glutCreateWindow("Futurattack - RJ Game Studio - 2009");
	glutKeyboardFunc(_kb_func);
	glutMouseFunc(_mouse_func);
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

	glutDisplayFunc(_display_func);
	glutTimerFunc(ENGINE_STEP,_timer_func,0);
	glutMainLoop();
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
			glutBitmapString(GLUT_BITMAP_HELVETICA_12,(const unsigned char *)_dbg_message);

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


	glutSwapBuffers();
}

inline void Engine::GLTimer()
{
	_ms_time += (float)ENGINE_STEP;

	//Effectue tous les calculs et changements de scene du gameplay, s'il existe
	if (_igameplay!=NULL)
		_igameplay->GameplayProcessing();

	if (_dbg_message_time>0.0)
		_dbg_message_time -= (float)ENGINE_STEP;

	glutPostRedisplay();
	glutTimerFunc(ENGINE_STEP,_timer_func,0);
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

void Engine::Release()
{
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




