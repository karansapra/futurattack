#pragma once

#include <hge.h>
#include <hgevector.h>

enum TYPE {BALL, SEGMENT, WHOLE};
typedef void (*CollideCallback)(int id1, int id2);

struct SolidBody
{
	int Id;
	bool Dynamic;
	TYPE Type;	
	SolidBody();

	virtual void Render();
};

struct DynamicObject : public SolidBody
{
	float fMass;
	hgeVector CurrentForce;
	hgeVector Center;
	hgeVector Center_1;
	hgeVector Velocity;
	hgeVector Velocity_1;
	float fF; //Frottement
	float fB; //Coefficient de rebond



	DynamicObject();
	virtual bool CollisionProcess(SolidBody &other_body) = 0;

	CollideCallback CollideCB;
	bool isMoving;
};


struct Wall : public SolidBody
{
	friend struct GolfBall;

	Wall(float Ax,float Ay, float Bx, float By);
	void Render();

	hgeVector A,B;

private:
	
	hgeQuad quad;
};

struct GolfBall : public DynamicObject
{
	float Radius;

	GolfBall(float x=0.0f, float y=0.0f, float r=20.0f);
	void Render();

	bool CollisionProcess(SolidBody &other_body);

private:
	hgeQuad quad;
};

struct Whole : public SolidBody
{
	float Radius;
	hgeVector Center;

	Whole(float x=0.0f, float y=0.0f, float r=20.0f);
	void Render();

private:
	hgeQuad quad;
};