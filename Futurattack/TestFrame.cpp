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

	_current_zoom = 1.0;
	_ycam = 0.0;

	_x = 0.0;
	_y = 0.0;
}

TestFrame::~TestFrame() {

}

void TestFrame::PreRender()
{
	//_camera->Move(1.2*sin(6.28*Engine::GetInstance().GetCurrentTime()/1000.0),0.0,0.0);
}

void TestFrame::Render()
{
	glPushMatrix();
	glRotatef(Engine::GetInstance().GetCurrentTime()*360.0/10000.0,0.0,1.0,0.0);
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f,0.0f,1.0f);
		glVertex3f(0.0,0.0,0.0);
		glColor3f(1.0f,1.0f,0.0f);
		glVertex3f(1.0,0.0,0.0);
		glColor3f(0.0f,1.0f,1.0f);
		glVertex3f(0.0,0.0,1.0);

		glColor3f(1.0f,0.0f,1.0f);
		glVertex3f(0.0,0.0,0.0);
		glColor3f(1.0f,1.0f,0.0f);
		glVertex3f(-1.0,0.0,0.0);
		glColor3f(0.0f,1.0f,1.0f);
		glVertex3f(0.0,0.0,-1.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.0,0.0,0.0);
		glRotatef(33.0,0.0,1.0,0.0);
		glColor3f(0.6f,0.6f,0.6f);
		glutSolidCube(0.7);
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


