#include "PhysicsObjects.h"
#include <stdio.h>

extern HGE * hge;

SolidBody::SolidBody()
{
	Id = -1;
	Dynamic = false;
	Type = BALL;
	
}

void SolidBody::Render()
{

}

DynamicObject::DynamicObject()
{
	CollideCB = NULL;
	isMoving = false;

	fMass = 0.166f;
	fF = 0.2f;
	fB = 0.7f;
}

Wall::Wall(float Ax,float Ay, float Bx, float By)
{
	Type = SEGMENT;

	A.x = Ax;
	A.y = Ay;
	B.x = Bx;
	B.y = By;

	quad.v[0].tx = 0.0; quad.v[0].ty = 0.0;
	quad.v[1].tx = 0.0; quad.v[1].ty = 1.0;
	quad.v[2].tx = 1.0; quad.v[2].ty = 1.0;
	quad.v[3].tx = 1.0; quad.v[3].ty = 0.0;		


	for (int i=0;i<4;i++)
	{
		quad.v[i].z = 0.5f;
		quad.v[i].col = 0xFFFFFFFF;
	}

	quad.tex = hge->Texture_Load("concrete.jpg");
	quad.blend=BLEND_ALPHAADD | BLEND_COLORMUL | BLEND_ZWRITE;
}

void Wall::Render()
{
	quad.v[0].x = A.x-1; quad.v[0].y = A.y+1;
	quad.v[1].x = A.x+1; quad.v[1].y = A.y-1;
	quad.v[2].x = B.x+1; quad.v[2].y = B.y-1;
	quad.v[3].x = B.x-1; quad.v[3].y = B.y+1;

	hge->Gfx_RenderQuad(&quad);
}

GolfBall::GolfBall(float x, float y, float r)
{
	Dynamic = true;
	Type = BALL;

	quad.v[0].tx = 0.0; quad.v[0].ty = 0.0;
	quad.v[1].tx = 0.0; quad.v[1].ty = 1.0;
	quad.v[2].tx = 1.0; quad.v[2].ty = 1.0;
	quad.v[3].tx = 1.0; quad.v[3].ty = 0.0;		
	for (int i=0;i<4;i++)
	{
		quad.v[i].z = 0.3f;
		quad.v[i].col = 0xFFFFFFFF;
	}

	quad.tex = hge->Texture_Load("ball7.png");
	quad.blend=BLEND_ALPHABLEND;
	
	Center.x = x;
	Center.y = y;
	Center_1.x = x;
	Center_1.y = y;
	Radius=r;
}


void GolfBall::Render()
{
	quad.v[0].x = Center.x-Radius; quad.v[0].y = Center.y-Radius;
	quad.v[1].x = Center.x-Radius; quad.v[1].y = Center.y+Radius;
	quad.v[2].x = Center.x+Radius; quad.v[2].y = Center.y+Radius;
	quad.v[3].x = Center.x+Radius; quad.v[3].y = Center.y-Radius;
	hge->Gfx_RenderQuad(&quad);
}


bool GolfBall::CollisionProcess(SolidBody &other_body)
{
	if (other_body.Dynamic)
		return false;

	if (other_body.Type==WHOLE)
	{
		Whole* w = (Whole*)&other_body;

		hgeVector D = w->Center-Center;
		if (D.Length()<(Radius+w->Radius)*0.7f && w->Center!=Center)
		{
			Velocity.x = 0;
			Velocity.y = 0;
			Center = w->Center;
			Center_1 = w->Center;
			CurrentForce.x = 0;
			CurrentForce.y = 0;
			return true;
		}
	}
	else if (other_body.Type==SEGMENT)
	{
		Wall* w = (Wall*)&other_body;
		hgeVector AB = w->B - w->A;

		//Normalized Segment
		hgeVector ABn = AB/AB.Length();
		hgeVector AC = Center - w->A;

		float d = AC.Dot(&ABn);
		if (d<0)
			d=0;
		if (d>AB.Length())
			d=AB.Length();
		
		//On calcule le point prévu de l'impact
		hgeVector ptimpact = d*ABn;
		ptimpact = ptimpact+w->A;
		hgeVector PC = Center-ptimpact;

		if (PC.Length()<Radius)
		{
			hgeVector PCn = PC/PC.Length();
			hgeVector PCTn;
			PCTn.x = PCn.y;
			PCTn.y = -PCn.x;

			//Computes the new Velocity vector
			float Vt = Velocity.Dot(&PCTn);
			float Vn = -Velocity.Dot(&PCn);
			Velocity.y = (Vt*PCn.x-Vn*PCTn.x)/(PCn.x*PCTn.y-PCn.y*PCTn.x);
			if (PCn.x!=0.0f)
				Velocity.x = (Vn-Velocity.y*PCn.y)/PCn.x;
			Velocity = Velocity*fB;
			return true;
		}
	}
	return false;
}

Whole::Whole(float x, float y, float r)
{
	Type = WHOLE;

	quad.v[0].tx = 0.0; quad.v[0].ty = 0.0;
	quad.v[1].tx = 0.0; quad.v[1].ty = 1.0;
	quad.v[2].tx = 1.0; quad.v[2].ty = 1.0;
	quad.v[3].tx = 1.0; quad.v[3].ty = 0.0;		
	for (int i=0;i<4;i++)
	{
		quad.v[i].z = 0.5f;
		quad.v[i].col = 0xFFFFFFFF;
	}

	quad.tex = hge->Texture_Load("trou.png");
	quad.blend=BLEND_ALPHABLEND;
	
	Center.x = x;
	Center.y = y;
	Radius=r;
}


void Whole::Render()
{
	quad.v[0].x = Center.x-Radius; quad.v[0].y = Center.y-Radius;
	quad.v[1].x = Center.x-Radius; quad.v[1].y = Center.y+Radius;
	quad.v[2].x = Center.x+Radius; quad.v[2].y = Center.y+Radius;
	quad.v[3].x = Center.x+Radius; quad.v[3].y = Center.y-Radius;
	hge->Gfx_RenderQuad(&quad);
}
