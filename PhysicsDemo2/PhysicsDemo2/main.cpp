#include <windows.h>

#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "core.h"
#include "tornado.h"
#include "particle.h"
#include "particleforcegenerator.h"
#include "rigidbody.h"

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
	RigidBody body1;
	RigidBody body2;
	
public:
	MyScene()
	{
		tornado = TornadoEngine::GetInstance();

		body1.position = Vector3(3,2,0);
		body1.SetSphereInertiaTensor(2,2);
		body1.SetDampingCoefficients(0.8,0.8);

		body2.position = Vector3(0,1,0);
		body2.SetSphereInertiaTensor(1,1);
		body2.SetDampingCoefficients(0.9,0.9);

		physic_world.AddBody(body1);
		physic_world.AddBody(body2);

		b = Buoyancy(Vector3(0.5,0,0),4,0.005,4.5);
		
		physic_world.fregistry.Add(body1,b);
		//physic_world.fregistry.Add(body2,b);

		//physic_world.fregistry.Add(body1,g);
		//physic_world.fregistry.Add(body2,g);
	}

	void PreRender()
	{		
		Vector3 newpos = body1.position+body2.position;
		newpos /= 2.0f;

		gluLookAt(
			10.0,10.0,20.0,
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
				Vector3 torque(0,100,0);
				body1.AddTorque(torque);
			}
			if ((jinfos.Buttons&XB360_B)!=0)
			{
				Vector3 torque(0,-100,0);
				body1.AddTorque(torque);
			}

			REAL threshold = 65535.0f/2.0f;

			REAL yforce = jinfos.analogA.y;
			if (yforce<threshold*0.8 || yforce>threshold*1.2)
			{
				yforce -= 65535.0f/2.0f;
				yforce /= -2000.0f;
			} else
			{
				yforce = 0;
			}
				
			REAL xforce = jinfos.analogA.x;
			if (xforce<threshold*0.8 || xforce>threshold*1.2)
			{
				xforce -= 65535.0f/2.0f;
				xforce /= 2000.0f;
			} else
			{
				xforce = 0;
			}

			body2.AddForceAtBodyPoint(Vector3(0,0,0),Vector3(xforce,yforce,0));
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

		body1.transform.FillOpenGLMatrix(matrix);
		glPushMatrix();
		glMultMatrixf(matrix);
		tornado->DrawSphere(2);
		glPopMatrix();

		body2.transform.FillOpenGLMatrix(matrix);
		glPushMatrix();
		glMultMatrixf(matrix);
		tornado->DrawSphere(1);
		glPopMatrix();

	}
};

void main(int argc, char **argv)
{
	MyScene myscene;
	TornadoEngine * tornado = TornadoEngine::GetInstance();	
	tornado->Init(myscene);
	tornado->Run();
}

