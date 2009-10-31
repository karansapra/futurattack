/*
 * Skybox.cpp
 *
 *  Created on: 28 oct. 2009
 *      Author: Clement
 */

#include "Skybox.h"

namespace CJEngine {

	GLenum cube[6] = {
			GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
			GL_TEXTURE_CUBE_MAP_POSITIVE_X,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	};

	Skybox::Skybox(const char * basename) {
		char buffer_name[256];

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
        float ambient[] = {1.0,1.0,1.0,1.0};

        float l0[] = {0.0,10.0,-10.0,1.0};
        glLightfv(GL_LIGHT0,GL_POSITION,l0);

        glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
        glLightfv(GL_LIGHT0,GL_DIFFUSE,ambient);



        glEnable(GL_TEXTURE_CUBE_MAP);
		glGenTextures(1,&_textures_gl[0]);
		glBindTexture(GL_TEXTURE_CUBE_MAP,_textures_gl[0]);
		glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
		glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

		for (int i=1;i<=6;i++)
		{
			sprintf(buffer_name,"%s%d.bmp",basename,i);
			_faces[i-1] = new BitmapTexture();
			_faces[i-1]->Load(buffer_name);

			glTexImage2D(cube[i-1],0,GL_RGBA,_faces[i-1]->GetWidth(),_faces[i-1]->GetHeight(),
					0,GL_RGBA,GL_UNSIGNED_BYTE,_faces[i-1]->GetPixelsData());



			delete _faces[i-1];
		}

		_skybox_size = 0.5f;
	}

	Skybox::~Skybox() {

	}

	void Skybox::SetSize(float size)
	{
		if (size>0.0)
			_skybox_size = size;
	}

	void Skybox::Render(float time)
	{
		glEnable(GL_TEXTURE_CUBE_MAP);
		glBindTexture(GL_TEXTURE_CUBE_MAP,_textures_gl[0]);
		glDisable(GL_TEXTURE_GEN_R);
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);


		glBegin(GL_QUADS);
			//LEFT
			glTexCoord3f(-1.0f,-1.0f,1.0f);
			glVertex3f(-_skybox_size,-_skybox_size,_skybox_size);

			glTexCoord3f(-1.0f,-1.0f,-1.0f);
			glVertex3f(-_skybox_size,-_skybox_size,-_skybox_size);

			glTexCoord3f(-1.0f,1.0f,-1.0f);
			glVertex3f(-_skybox_size,_skybox_size,-_skybox_size);

			glTexCoord3f(-1.0f,1.0f,1.0f);
			glVertex3f(-_skybox_size,_skybox_size,_skybox_size);

			//RIGHT
			glTexCoord3f(1.0f,-1.0f,1.0f);
			glVertex3f(_skybox_size,-_skybox_size,_skybox_size);

			glTexCoord3f(1.0f,1.0f,1.0f);
			glVertex3f(_skybox_size,_skybox_size,_skybox_size);

			glTexCoord3f(1.0f,1.0f,-1.0f);
			glVertex3f(_skybox_size,_skybox_size,-_skybox_size);

			glTexCoord3f(1.0f,-1.0f,-1.0f);
			glVertex3f(_skybox_size,-_skybox_size,-_skybox_size);

			//BACK
			glTexCoord3f(1.0f,1.0f,-1.0f);
			glVertex3f(_skybox_size,_skybox_size,-_skybox_size);

			glTexCoord3f(-1.0f,1.0f,-1.0f);
			glVertex3f(-_skybox_size,_skybox_size,-_skybox_size);

			glTexCoord3f(-1.0f,-1.0f,-1.0f);
			glVertex3f(-_skybox_size,-_skybox_size,-_skybox_size);

			glTexCoord3f(1.0f,-1.0f,-1.0f);
			glVertex3f(_skybox_size,-_skybox_size,-_skybox_size);

			//FRONT
			glTexCoord3f(1.0f,1.0f,1.0f);
			glVertex3f(_skybox_size,_skybox_size,_skybox_size);

			glTexCoord3f(1.0f,-1.0f,1.0f);
			glVertex3f(_skybox_size,-_skybox_size,_skybox_size);

			glTexCoord3f(-1.0f,-1.0f,1.0f);
			glVertex3f(-_skybox_size,-_skybox_size,_skybox_size);

			glTexCoord3f(-1.0f,1.0f,1.0f);
			glVertex3f(-_skybox_size,_skybox_size,_skybox_size);

			//TOP
			glTexCoord3f(1.0f,1.0f,1.0f);
			glVertex3f(_skybox_size,_skybox_size,_skybox_size);

			glTexCoord3f(-1.0f,1.0f,1.0f);
			glVertex3f(-_skybox_size,_skybox_size,_skybox_size);

			glTexCoord3f(-1.0f,1.0f,-1.0f);
			glVertex3f(-_skybox_size,_skybox_size,-_skybox_size);

			glTexCoord3f(1.0f,1.0f,-1.0f);
			glVertex3f(_skybox_size,_skybox_size,-_skybox_size);

			//BOTTOM
			glTexCoord3f(1.0f,-1.0f,1.0f);
			glVertex3f(_skybox_size,-_skybox_size,_skybox_size);

			glTexCoord3f(1.0f,-1.0f,-1.0f);
			glVertex3f(_skybox_size,-_skybox_size,-_skybox_size);

			glTexCoord3f(-1.0f,-1.0f,-1.0f);
			glVertex3f(-_skybox_size,-_skybox_size,-_skybox_size);

			glTexCoord3f(-1.0f,-1.0f,1.0f);
			glVertex3f(-_skybox_size,-_skybox_size,_skybox_size);




		glEnd();
	}

}
