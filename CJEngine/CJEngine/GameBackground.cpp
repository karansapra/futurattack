/*
 * GameBackground.cpp
 *
 *  Created on: 30 oct. 2009
 *      Author: Clement
 */

#include "GameBackground.h"

GameBackground::GameBackground() {
	_engine_instance = Engine::GetInstance();
	_sb = new Skybox("C:\\sky1\\side");
	_sb->SetSize(2000.0);
	_camera_fond = new PerspectiveCam();
	eye[0] = 200.0;
	lookat[0] = 200.0;
	eye[1] = 180.0;	
	eye[2] = 200.0;

	eye_target[0] = 200.0;
	lookat_target[0] = 200.0;
	eye_target[1] = 180.0;
	eye_target[2] = 200.0;

	_camera_fond->SetLookAtPosition(lookat);
	_camera_fond->SetEyePosition(eye);
}

GameBackground::~GameBackground() 
{

}

void GameBackground::PreRender()
{

}

void GameBackground::RenderCase(float size)
{
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_CUBE_MAP);
	glBegin(GL_QUADS);
		glColor3f(1.0,0.5,0.5);
		glVertex3f(-size,0.0,size);
		glVertex3f(size,0.0,size);
		glVertex3f(size,0.0,-size);
		glVertex3f(-size,0.0,-size);
	glEnd();
}

void GameBackground::Move(float x, float z)
{
	eye_target[0]+=x;
	lookat_target[0]+=x;

	eye_target[2]+=z;
	lookat_target[2]+=z;
}

void GameBackground::Render(float time)
{	
	glPushMatrix();

	lookat = lookat + (lookat_target-lookat)*0.2f;
	eye = eye + (eye_target-eye)*0.15f;

	_camera_fond->SetLookAtPosition(lookat);
	_camera_fond->SetEyePosition(eye);

	_engine_instance->SetCamera(*_camera_fond);
	_sb->Render(time);

	for (int z=0;z<16;z++)
	{		
		glPushMatrix();
		for (int x=0;x<16;x++)
		{
			glTranslatef(42.0f,0.0,0.0);
			RenderCase(20.0);
		}
		glPopMatrix();
		glTranslatef(0.0,0.0,42.0f);
	}
	
	glPopMatrix();
	
}

