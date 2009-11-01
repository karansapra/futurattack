/*
 * GameBackground.cpp
 *
 *  Created on: 30 oct. 2009
 *      Author: Clement
 */

#include "GameBackground.h"

GameBackground::GameBackground() {
	_engine_instance = Engine::GetInstance();

	//Skybox
	_sb = new Skybox("C:\\cubemap\\cubemap");
	_sb->SetSize(2000.0);

	for (int i=0;i<11*11;i++)
		_data_grid[i] = 0;

	BitmapTexture arbre;
	arbre.Load("C:\\terre.bmp");
	glGenTextures(1,_ground_texture);
	glBindTexture(GL_TEXTURE_2D,_ground_texture[0]);
	gluBuild2DMipmaps(GL_TEXTURE_2D,4,arbre.GetWidth(),arbre.GetHeight(),GL_RGBA,GL_UNSIGNED_BYTE,arbre.GetPixelsData());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);


	_camera_fond = new PerspectiveCam();

	lookat_target[0] = 200.0;
	lookat_target[2] = 200.0;
	eye_target[0] = 200.0;
	eye_target[1] = 120.0;
	eye_target[2] = 400.0;

	_camera_fond->SetLookAtPosition(lookat);
	_camera_fond->SetEyePosition(eye);

	lamp_lookat[0] = 150.0;
	lamp_lookat[2] = 150.0;
	lamp_position[1] = 300.0;

	_lamp_camera = new PerspectiveCam(70.0);
	_lamp_camera->SetLookAtPosition(lamp_lookat);
	_lamp_camera->SetEyePosition(lamp_position);

	switch_cam = false;
	take_photo = false;
	_select = false;

	_forest = new Forest(15.0,400.0,400.0,100,"C:\\arbre.bmp");
}

GameBackground::~GameBackground() 
{
	delete _lamp_camera;
	delete _camera_fond;
}

void GameBackground::PreRender()
{

}

void GameBackground::RenderCase(float size)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,_ground_texture[0]);
	glBegin(GL_QUADS);
		glColor4f(1.0,1.0,1.0,1.0);
		glTexCoord2f(0.0,0.0);
		glVertex3f(-size,0.0,size);
		glTexCoord2f(1.5,0.0);
		glVertex3f(size,0.0,size);
		glTexCoord2f(1.5,1.5);
		glVertex3f(size,0.0,-size);
		glTexCoord2f(0.0,1.5);
		glVertex3f(-size,0.0,-size);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void GameBackground::Move(float x, float z)
{
	eye_target[0]+=x;
	lookat_target[0]+=x;

	eye_target[2]+=z;
	lookat_target[2]+=z;
}

void GameBackground::SelectionMode(int x, int y)
{
	static GLuint selectBuffer[64];
	float aspect;
	GLint hits, viewport[4];

	glSelectBuffer(64,selectBuffer);
	glGetIntegerv(GL_VIEWPORT,viewport);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glRenderMode(GL_SELECT);
	glLoadIdentity();
	gluPickMatrix(x,viewport[3]-y,2,2,viewport);

	_select = true;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Render(_engine_instance->GetSecondsElapsed());
	_select = false;

	hits = glRenderMode(GL_RENDER);

	for (int i=0;i<hits;i++)
	{
		printf("Hits %u : %d\n",hits,selectBuffer[3+4*i]);
	}
	printf("\n");

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
}

void GameBackground::Render(float time)
{
	if (take_photo)
	{
		_forest->DeleteTrees(0,0,100,100);
		take_photo = false;
	}

	glInitNames();
	glPushName(0);

	glPushMatrix();	

	lookat = lookat + (lookat_target-lookat)*0.2f;
	eye = eye + (eye_target-eye)*0.15f;

	_camera_fond->SetLookAtPosition(lookat);
	_camera_fond->SetEyePosition(eye);

	_engine_instance->SetCamera(*_camera_fond);

	glColor4f(1.0,1.0,1.0,1.0);

	glPushMatrix();
	_sb->Render(time);
	glPopMatrix();

	glPushMatrix();


	for (int z=0;z<11;z++)
	{		
		glPushMatrix();
		for (int x=0;x<11;x++)
		{
			glLoadName(z*11+x+1);
			if (_data_grid[z*11+x]==0)
				RenderCase(20.0);

			glTranslatef(40.0f,0.0,0.0);
		}
		glPopMatrix();
		glTranslatef(0.0,0.0,40.0f);
	}	
	glPopMatrix();

	glLoadName(300);
	//Draw forest
	glTranslatef(200.0,0,200.0);
	_forest->Render(time);

	glPopMatrix();
}
