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
	_camera->Zoom(2.1);

	_current_zoom = 2.1;
	_ycam = 0.0;

	_x = 0.0;
	_y = 0.0;

	//Chargement de la texture
	_sraster = new BitmapTexture();
	_ground = new BitmapTexture();
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

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
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
	//_camera->Move(1.2*sin(6.28*Engine::GetInstance().GetCurrentTime()/1000.0),0.0,0.0);
}

void TestFrame::Render()
{
	glPushMatrix();
		glRotatef(37.0,1.0,0.0,0.0);
		glRotatef(Engine::GetInstance().GetCurrentTime()*360.0/3800.0,0.0,1.0,0.0);

		// Plan
		glBindTexture(GL_TEXTURE_2D,_textures[1]);
		glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(5.0f, -1.0f, -5.0f);	// Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f, -1.0f, -5.0f);	// Top Left Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0f, -1.0f,  5.0f);	// Bottom Left Of The Texture and Quad
			glTexCoord2f(1.0f, 1.0f); glVertex3f(5.0f, -1.0f,  5.0f);	// Bottom Right Of The Texture and Quad
		glEnd();


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
		_ycam+=2.0;
	} else if (key=='s' && _current_zoom>0.3)
	{
		_ycam-=2.0;
	} else if (key=='l')
	{
		_x+=2.0;
	} else if (key=='j')
	{
		_x-=2.0;
	} else if (key=='k')
	{
		_y-=2.0;
	} else if (key=='i')
	{
		_y+=2.0;
	}
	_camera->SetEyePosition(0.0,_ycam,10.0);
	_camera->Move(_x,_y,0.0);
}

void TestFrame::ButtonPressed(unsigned char button, int x, int y)
{
	if (button==3)
	{
		_current_zoom+=0.2;
	} else if (button==4 && _current_zoom>0.3)
	{
		_current_zoom-=0.2;
	}
	_camera->Zoom(_current_zoom);
}


