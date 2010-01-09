#include "forcegenerator.h"
#include "rigidbody.h"


/*
GRAVITY FORCE GENERATOR
*/

Gravity::Gravity()
{
	gravity = Vector3(0,(REAL)-9.81,0);
}

Gravity::Gravity(const Vector3 & gravity) :
gravity(gravity)
{
}

void Gravity::ForceUpdate(RigidBody & body, REAL dt)
{
	if (body.HasInfiniteMass())
		return;

	body.AddForce(gravity*body.GetMass());
}


Buoyancy::Buoyancy()
{

}

Buoyancy::Buoyancy(const Vector3 & cofb,REAL maxDepth, REAL volume, REAL waterheight, REAL liquidDensity) :
center_of_buoyancy(cofb), maxDepth(maxDepth), volume(volume), waterHeight(waterheight), liquidDensity(liquidDensity)
{
	
}

void Buoyancy::ForceUpdate(RigidBody & body, REAL dt)
{
    // Calculate the submersion depth
    Vector3 pointInWorld = body.transform * center_of_buoyancy;
    REAL depth = pointInWorld.y;

    // Check if we're out of the water
    if (depth >= waterHeight + maxDepth) return;
    Vector3 force;

    // Check if we're at maximum depth
    if (depth <= waterHeight - maxDepth)
    {
        force.y = liquidDensity * volume;
		body.AddForceAtBodyPoint(center_of_buoyancy,force);
        return;
    }

    // Otherwise we are partly submerged
    force.y = liquidDensity * volume *
        (depth - maxDepth - waterHeight) / (2 * maxDepth);
	body.AddForceAtBodyPoint(center_of_buoyancy,force);
}