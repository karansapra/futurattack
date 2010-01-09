#ifndef FORCEGENERATOR_H
#define FORCEGENERATOR_H

#include "types.h"
#include "core.h"

struct RigidBody;

/*
Interface for rigid bodies force generators
*/
struct IForceGenerator
{
	virtual void ForceUpdate(RigidBody & body, REAL dt)=0;
};

/*
Gravity field generator
*/
class Gravity : public IForceGenerator
{
	Vector3 gravity;
public:
	Gravity();
	Gravity(const Vector3 & gravity);
	virtual void ForceUpdate(RigidBody & body, REAL dt);
};

class Buoyancy : public IForceGenerator
{
public:
	REAL maxDepth;
	REAL volume;
	REAL waterHeight;
	REAL liquidDensity;

	/*
	Body coordinates
	*/
	Vector3 center_of_buoyancy;

	Buoyancy();
	Buoyancy(const Vector3 & cofb,REAL maxDepth, REAL volume, REAL waterheight, REAL liquidDensity=1000.0);
	
	virtual void ForceUpdate(RigidBody & body, REAL dt);

};

#endif
