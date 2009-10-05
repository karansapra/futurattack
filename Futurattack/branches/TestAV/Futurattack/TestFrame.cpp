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

	_camera->SetEyePosition(0.0,0.0,10.0);
	_camera->SetVolumeView(-width/100.0,width/100.0,height/100.0,-height/100.0,0.00001,10000.0);
	_camera->SetLookAtPosition(0.0,0.0,0.0);
	_camera->Zoom(1.0);

	_current_zoom = 1.0;
	_ycam = 0.0;

	_x = 0.0;
	_y = 0.0;

	//Chargement de la texture
	_sraster = new BitmapTexture();
	_ground = new BitmapTexture();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	float ambient[] = {1.0,1.0,1.0,1.0};

	glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,ambient);

	if (_sraster->Load("/home/clement/Bureau/Logo2.bmp") && _ground->Load("/home/clement/Bureau/Ground.bmp"))
	{
		glEnable(GL_TEXTURE_2D);
		glGenTextures(2,_textures);

		glBindTexture(GL_TEXTURE_2D,_textures[0]);
		glTexImage2D(GL_TEXTURE_2D,0,_sraster->GetBPP()/8,_sraster->GetWidth(),_sraster->GetHeight(),0,GL_RGB,GL_UNSIGNED_BYTE,_sraster->GetPixelsData());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
		glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

		glBindTexture(GL_TEXTURE_2D,_textures[1]);
		glTexImage2D(GL_TEXTURE_2D,0,_ground->GetBPP()/8,_ground->GetWidth(),_ground->GetHeight(),0,GL_RGB,GL_UNSIGNED_BYTE,_ground->GetPixelsData());

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	}

	delete _sraster;
	delete _ground;

	Engine::GetInstance().ShowDebugMessage("Version Alpha Release 0.1\nC.JACOB");

	//Lumiere
}

TestFrame::~TestFrame() {

}

bool TestFrame::AnimationFinished()
{
	return false;
}

void TestFrame::PreRender()
{
	_camera->Zoom(0.5+0.14*sin(6.28*Engine::GetInstance().GetCurrentTime()/40000.0));
	_camera->SetEyePosition(0.0,_ycam + 2.0*sin(6.28*Engine::GetInstance().GetCurrentTime()/22600.0),10.0);
}

void TestFrame::Render()
{
	glEnable(GL_BLEND);
	glColor4f(1.0,1.0,1.0,1.0);
	glPushMatrix();
		glRotatef(Engine::GetInstance().GetCurrentTime()*360.0/16800.0,0.0,1.0,0.0);
		float lx = 2.0*cos(Engine::GetInstance().GetCurrentTime()*6.28/1000.0);
		float ly = 2.0*sin(Engine::GetInstance().GetCurrentTime()*6.28/1000.0);
		float l0[] = {lx,10.0,ly,1.0};
		glLightfv(GL_LIGHT0,GL_POSITION,l0);

		// Plan
		glBindTexture(GL_TEXTURE_2D,_textures[1]);
		glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(50.0f, -1.0f, -50.0f);	// Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0f, -1.0f, -50.0f);	// Top Left Of The Texture and Quad
			glTexCoord2f(0.0f, 10.0f); glVertex3f(-50.0f, -1.0f,  50.0f);	// Bottom Left Of The Texture and Quad
			glTexCoord2f(1.0f, 10.0f); glVertex3f(50.0f, -1.0f,  50.0f);	// Bottom Right Of The Texture and Quad
		glEnd();

		glColor4f(1.0,1.0,1.0,1.0);
		glBindTexture(GL_TEXTURE_2D,_textures[0]);
		glBegin(GL_QUADS);
			// Front Face
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
			// Back Face
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
			// Top Face
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
			// Bottom Face
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Top Left Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
			// Right face
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
			// Left Face
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glEnd();

		glColor4f(0.07,0.5,0.99,0.5);
		glutSolidSphere(3.0,32,32);

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
		_ycam+=0.02;
	} else if (key=='s')
	{
		_ycam-=0.02;
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
	_camera->SetEyePosition(0.0,_ycam,10.0);
	_camera->Move(_x,_y,0.0);
}

void TestFrame::ButtonPressed(unsigned char button, int x, int y)
{
	if (button==3 && _current_zoom<1.0)
	{
		Engine::GetInstance().Release();
	} else if (button==4 && _current_zoom>0.05)
	{
		_current_zoom-=0.02;
	}
	_camera->Zoom(_current_zoom);
}


