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
	_ycam = 0.0;

	_x = 0.0;
	_y = 0.0;

	//Chargement de la texture
	_sraster = new BitmapTexture();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	float ambient[] = {1.0,1.0,1.0,1.0};

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

	//Lumiere
	_obj = new OBJ3DObject();
	_obj->SwitchTextureOrigin();
	_obj->Load("/home/clement/Bureau/Case.obj");
}

TestFrame::~TestFrame() {
	delete _obj;
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
	glEnable(GL_BLEND);
	glColor4f(1.0,1.0,1.0,1.0);
	glPushMatrix();
		glRotatef(Engine::GetInstance().GetCurrentTime()*360.0/16800.0,0.0,1.0,0.0);
		float lx = 5.0*cos(Engine::GetInstance().GetCurrentTime()*6.28/1000.0);
		float ly = 5.0*sin(Engine::GetInstance().GetCurrentTime()*6.28/1000.0);
		float l0[] = {lx,0.0,ly,1.0};
		glLightfv(GL_LIGHT0,GL_POSITION,l0);
		glPushMatrix();
			glDisable(GL_LIGHTING);
			glTranslatef(lx,0.0,ly);
			glColor4f(1.0,1.0,1.0,1.0);
			glutSolidSphere(0.2,32,32);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glColor4f(0.6,0.6,0.6,1.0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,_textures[0]);

		float spec[] = {0.8,0.8,0.8,1.0};
		glMaterialfv(GL_FRONT,GL_SPECULAR,spec);
		glMateriali(GL_FRONT,GL_SHININESS,158);
		glEnable(GL_COLOR_MATERIAL);

		glFrontFace(GL_CCW);
		_obj->Render();
		glFrontFace(GL_CW);
		_obj->Render();
		glDisable(GL_COLOR_MATERIAL);

	glPopMatrix();
}

const char *TestFrame::ToString()
{
	return "TestFrame";
}

void TestFrame::KeyPressed(char key)
{
	if (key=='z')
	{
		_ycam+=0.2;
	} else if (key=='s')
	{
		_ycam-=0.2;
	} else if (key=='l')
	{
		_x+=0.02;
	} else if (key=='j')
	{
		_x-=0.02;
	} else if (key=='k')
	{
		_y-=0.02;
	} else if (key=='i')
	{
		_y+=0.02;
	}
	_camera->SetEyePosition(0.0,_ycam,3.0);
	_camera->Move(_x,_y,0.0);
}

void TestFrame::ButtonPressed(unsigned char button, int x, int y)
{
	if (button==3 && _current_zoom<1.6)
	{
		_current_zoom+=0.02;
	} else if (button==4 && _current_zoom>0.05)
	{
		_current_zoom-=0.02;
	}
	_camera->Zoom(_current_zoom);
}


