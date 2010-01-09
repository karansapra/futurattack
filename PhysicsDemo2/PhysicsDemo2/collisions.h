#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "types.h"
#include "core.h"
#include "rigidbody.h"

struct Primitive
{
	RigidBody * body;	
};

struct Sphere : public Primitive
{
	REAL radius;
};

struct Contact
{
	Vector3 contact_point;
	Vector3 contact_normal;
	REAL penetration;
};

struct CollisionData
{
	Contact * contacts;
	U16 contacts_lefts;

};

U16 DetectSphereAndSphere(Sphere & one, Sphere & two, CollisionData & data);

#endif
