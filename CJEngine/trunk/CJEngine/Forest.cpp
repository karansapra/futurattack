#include "Forest.h"

namespace CJEngine
{
	Forest::Forest(float tree_size, float width, float height, int qty, const char * billboard_filename)
	{
		_tree_size = new float[qty];
		_posx = new float[qty];
		_posy = new float[qty];
		_angle = new float[qty];

		srand(time(NULL));

		for (int i=0;i<qty;i++)
		{
			_tree_size[i] = tree_size + tree_size*((float)(rand()%100))/200.0f;

			_posx[i] = (((float)(rand()%100))/100.0f)*width - width/2.0f;
			_posy[i] = (((float)(rand()%100))/100.0f)*height - height/2.0f;

			_angle[i] = (float)(rand()%360);
		}



		_w = width;
		_h = height;
		_qty = qty;
		_billboard_filename = (char*)billboard_filename;

		_setup_tree();
	}

	void Forest::_setup_tree()
	{
		BitmapTexture arbre;
		arbre.Load(_billboard_filename);
		glGenTextures(1,_tree_texture);
		glBindTexture(GL_TEXTURE_2D,_tree_texture[0]);
		if ((arbre.GetBPP()/8)==4)
			gluBuild2DMipmaps(GL_TEXTURE_2D,4,arbre.GetWidth(),arbre.GetHeight(),GL_RGBA,GL_UNSIGNED_BYTE,arbre.GetPixelsData());
		else
			gluBuild2DMipmaps(GL_TEXTURE_2D,3,arbre.GetWidth(),arbre.GetHeight(),GL_RGB,GL_UNSIGNED_BYTE,arbre.GetPixelsData());
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
		glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
		
		_list = glGenLists(1);
		glNewList(_list,GL_COMPILE);

		glFrontFace(GL_CW);
		glBegin(GL_QUADS);			
			glTexCoord2f(0.0,1.0);
			glVertex3f(-1,0.0,0.0);
			glTexCoord2f(1.0,1.0);
			glVertex3f(1.0,0.0,0.0);
			glTexCoord2f(1.0,0.0);
			glVertex3f(1.0,2.0,0.0);
			glTexCoord2f(0.0,0.0);
			glVertex3f(-1.0,2.0,0.0);
		glEnd();
		glFrontFace(GL_CCW);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0,1.0);
			glVertex3f(-1,0.0,0.0);
			glTexCoord2f(1.0,1.0);
			glVertex3f(1.0,0.0,0.0);
			glTexCoord2f(1.0,0.0);
			glVertex3f(1.0,2.0,0.0);
			glTexCoord2f(0.0,0.0);
			glVertex3f(-1.0,2.0,0.0);
		glEnd();
		glRotatef(90.0f,0.0,1.0,0.0);
		glFrontFace(GL_CW);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0,1.0);
			glVertex3f(-1,0.0,0.0);
			glTexCoord2f(1.0,1.0);
			glVertex3f(1.0,0.0,0.0);
			glTexCoord2f(1.0,0.0);
			glVertex3f(1.0,2.0,0.0);
			glTexCoord2f(0.0,0.0);
			glVertex3f(-1.0,2.0,0.0);
		glEnd();
		glFrontFace(GL_CCW);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0,1.0);
			glVertex3f(-1,0.0,0.0);
			glTexCoord2f(1.0,1.0);
			glVertex3f(1.0,0.0,0.0);
			glTexCoord2f(1.0,0.0);
			glVertex3f(1.0,2.0,0.0);
			glTexCoord2f(0.0,0.0);
			glVertex3f(-1.0,2.0,0.0);
		glEnd();

		glEndList();
	}

	Forest::~Forest(void)
	{
		glDeleteLists(_list,1);
		delete[] _tree_size;
		delete[] _posx;
		delete[] _posy;
	}

	void Forest::DeleteTrees(int x, int y, int width, int height)
	{
		float width2 = width/2.0f;
		float height2 = height/2.0f;

		float limx_inf = x-width2;
		float limx_sup = x+width2;

		float limy_inf = y-height2;
		float limy_sup = y+height2;

		for (int i=0;i<_qty;i++)
		{
			if (_posx[i]>=limx_inf && _posx[i]<=limx_sup
				&& _posy[i]>=limy_inf && _posy[i]<=limy_sup && _tree_size[i]>0.0f)
			{
				_tree_size[i] = -_tree_size[i];
			}
		}
	}

	void Forest::Render(float time)
	{
		static float dt = 0.0f;
		dt = time-dt;

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D,_tree_texture[0]);		

		glPushMatrix();					
			for (int i=0;i<_qty;i++)
			{
				//Si l'arbre n'est pas detruit
				if (_tree_size[i]>0.0f)
				{
					glPushMatrix();
					glTranslatef(_posx[i],0.0,_posy[i]);
					glRotatef(_angle[i],0.0,1.0,0.0);
					glScalef(_tree_size[i],_tree_size[i],_tree_size[i]);	
					glColor4f(1.0,1.0,1.0,1.0);
					glCallList(_list);
					glPopMatrix();
				} else if (_tree_size[i]<0.8f)
				{
					_tree_size[i] = _tree_size[i] - _tree_size[i]*0.01f*dt;
					glPushMatrix();
					glTranslatef(_posx[i],0.0,_posy[i]);
					glRotatef(_angle[i],0.0,1.0,0.0);
					glScalef(-_tree_size[i],-_tree_size[i],-_tree_size[i]);	
					glColor4f(1.0,1.0,1.0,0.5f);
					glCallList(_list);
					glPopMatrix();
				}
			}			
		glPopMatrix();

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	}

}