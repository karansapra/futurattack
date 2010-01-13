#include <windows.h>

#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "core.h"
#include "tornado.h"
#include "particle.h"
#include "particleforcegenerator.h"
#include "rigidbody.h"
#include "objfileloader.h"
#include "stack.h"

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/glut.h"
#include <stdio.h>


class MyScene : public IRenderable
{
	TornadoEngine * tornado;	

	Gravity g;
	Buoyancy b;
	
	World physic_world;
	RigidBody car;

	Mesh mesh;

public:
	MyScene()
	{
		tornado = TornadoEngine::GetInstance();

		LoadObjFile((U8*)"untitled.obj",mesh);

		car.SetSphereInertiaTensor(1.0,10.0);
		car.SetDampingCoefficients(0.7,0.7);

		physic_world.AddBody(car);

	}

	void PreRender()
	{		
		Vector3 dir = car.transform.TransformDirection(Vector3(0,0,-10));
		Vector3 newpos = car.position;		
		dir = newpos-dir;
		dir.y = 5;

		gluLookAt(
			dir.x,dir.y,dir.z,
			newpos.x,newpos.y,newpos.z,
			0.0,1.0,0.0
			);
	}
	

	void Render()
	{
		static REAL last_time;
		
		physic_world.StartFrame();

		JOYSTICK_INFOS jinfos = tornado->GetJoystickState();
		if (jinfos.Plugged)
		{
			if ((jinfos.Buttons&XB360_A)!=0)
			{
				car.AddForceAtBodyPointAndForceInBodySpace(Vector3(),Vector3(0,0,-150));
			}
			if ((jinfos.Buttons&XB360_X)!=0)
			{
				car.AddForceAtBodyPointAndForceInBodySpace(Vector3(),Vector3(0,0,150));
			}

			REAL threshold = 65535.0f/2.0f;

			REAL xforce = jinfos.analogA.x;
			if (xforce<threshold*0.8 || xforce>threshold*1.2)
			{
				xforce -= 65535.0f/2.0f;
				xforce /= 2000.0f;
			} else
			{
				xforce = 0;
			}
			car.AddForceAtBodyPointAndForceInBodySpace(Vector3(0,0,-2),Vector3(xforce,0,0));

		}

		

		//tornado->DrawLine(body1.transform.TransformDirection(body1.GetTorqueAccumulatorValue()),body1.position);

		/*
		Time calculations
		*/
		REAL time = tornado->GetTime();
		REAL dt = time-last_time;
		last_time = time;

		/*
		Physic World calculations
		*/
		physic_world.RunPhysics(dt);

		/*
		3D Representation in OpenGL
		*/
		GLfloat matrix[16];

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		GLfloat position[] = {0.0,80.0,0.0,1.0};
		GLfloat ambdif[] = {0.7,0.7,0.7,1.0};
		GLfloat specular[] = {1.0,1.0,1.0,1.0};

		glShadeModel(GL_SMOOTH);
		glPushMatrix();
		glLightfv(GL_LIGHT0,GL_POSITION,position);
		glLightfv(GL_LIGHT0,GL_AMBIENT,ambdif);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,ambdif);
		glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
		glPopMatrix();

		glEnable(GL_NORMALIZE);
		//glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
		glMateriali(GL_FRONT,GL_SHININESS,10);
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular);

		car.transform.FillOpenGLMatrix(matrix);
		glPushMatrix();
		glMultMatrixf(matrix);
		tornado->DrawMesh(mesh);
		glPopMatrix();
	}
};

void CalcOBB(VertexArray & varray)
{
	VertexArray::iterator i;

	Vector3 center;
	Vector3 axes[3];
	Vector3 widths;

	for (i=varray.begin();i<varray.end();i++)
	{
		
	}
}

StackAllocator st;

void main(int argc, char **argv)
{
	MyScene myscene;
	TornadoEngine * tornado = TornadoEngine::GetInstance();	
	tornado->Init(myscene);
	tornado->Run();
}

