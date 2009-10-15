/*
 * TestFrame.cpp
 *
 *  Created on: 1 oct. 2009
 *      Author: clement
 */

#include "TestFrame.h"

TestFrame::TestFrame() : IViewable() {
	float width = Engine::GetInstance().GetScreenWidth();
	float height = Engine::GetInstance().GetScreenHeight();

	_camera->SetEyePosition(0.0,3.0,30.0);
	_camera->SetVolumeView(-width/100.0,width/100.0,height/100.0,-height/100.0,0.00001,10000.0);
	_camera->SetLookAtPosition(0.0,0.0,0.0);
	_camera->Zoom(1.0);

	_current_zoom = 1.0;
	_ycam = 10.0;

	_x = 0.0;
	_y = 0.0;

	//Chargement de la texture
	_sraster = new BitmapTexture();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	float ambient[] = {1.0,1.0,1.0,1.0};

	float l0[] = {0.0,10.0,0.0,1.0};
	glLightfv(GL_LIGHT0,GL_POSITION,l0);

	glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,ambient);

	if (_sraster->Load("/home/clement/Bureau/Missile_Circle.bmp"))
	{
		glEnable(GL_TEXTURE_2D);
		glGenTextures(1,_textures);

		glBindTexture(GL_TEXTURE_2D,_textures[0]);
		glTexImage2D(GL_TEXTURE_2D,0,_sraster->GetBPP()/8,_sraster->GetWidth(),_sraster->GetHeight(),0,GL_RGBA,GL_UNSIGNED_BYTE,_sraster->GetPixelsData());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);
		glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

	}

	delete _sraster;

	Engine::GetInstance().ShowDebugMessage("Version Alpha Release 0.1\nC.JACOB");

	//Chargement des cases du plateau
	_base_case = new OBJ3DObject();
	_base_case->SwitchTextureOrigin();
	_base_case->Load("/home/clement/Bureau/Case2.obj");
}

TestFrame::~TestFrame() {
	delete _base_case;
}

bool TestFrame::AnimationFinished()
{
	return false;
}

void TestFrame::PreRender()
{
	_camera->SetEyePosition(0.0,_ycam,30.0);
}

void TestFrame::Render()
{
	glColor4f(1.0,1.0,1.0,1.0);
	glPushMatrix();
		glRotatef(Engine::GetInstance().GetCurrentTime()*360.0/16800.0,0.0,1.0,0.0);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,_textures[0]);

		glFrontFace(GL_CCW);
		glTranslatef(0.0,0.0,-5.0*2.5/2.0);
		for (int y=0;y<5;y++)
		{
			glTranslatef(0.0,0.0,2.5);
			glPushMatrix();
			glTranslatef(-10.0*2.5/2.0,0.0,0.0);
			for (int x=0;x<10;x++)
			{
				glTranslatef(2.5,0.0,0.0);
				_base_case->Render();
			}
			glPopMatrix();
		}


	glPopMatrix();
}

const char *TestFrame::ToString()
{
	return "TestFrame";
}

void TestFrame::KeyPressed(char key)
{
	//printf("key:%x ==> %c\n",key,key);
	if (key==KEYCODE_Z)
	{
		_ycam+=0.2;
	} else if (key==KEYCODE_S)
	{
		_ycam-=0.2;
	} else if (key==KEYCODE_RIGHT)
	{
		_x+=0.02;
	} else if (key==KEYCODE_LEFT)
	{
		_x-=0.02;
	} else if (key==KEYCODE_DOWN)
	{
		_y-=0.02;
	} else if (key==KEYCODE_UP)
	{
		_y+=0.02;
	} else if (key==KEYCODE_Q)
	{
		exit(0);
	}
	_camera->SetEyePosition(0.0,_ycam,3.0);
	_camera->Move(_x,_y,0.0);
}

void TestFrame::ButtonPressed(unsigned char button, int x, int y)
{
	if (button==MOUSE_CENTER_UP && _current_zoom<1.0)
	{
		_current_zoom+=0.02;
	} else if (button==MOUSE_CENTER_DOWN && _current_zoom>0.05)
	{
		_current_zoom-=0.02;
	}
	_camera->Zoom(_current_zoom);
}


