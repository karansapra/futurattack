#include "Particle.h"

#include <stdio.h>

Particle::Particle()
{
	damping = (REAL)0.9;
	inv_mass = (REAL)1.0;
	acceleration.y = (REAL)-15.0;
}

Particle::Particle(const Vector3 &initial_position)
{
	damping = (REAL)0.9;
	inv_mass = (REAL)1.0;
	acceleration.y = (REAL)-15.0;
	position = initial_position;
}

Particle::Particle(const Vector3 &initial_position,const Vector3 &initial_velocity)
{
	damping = (REAL)0.9;
	inv_mass = (REAL)1.0;
	acceleration.y = (REAL)-15.0;
	position = initial_position;
	velocity = initial_velocity;
}

void Particle::Integrate(REAL dt)
{
	if (inv_mass <= 0.0f) 
		return;

	if (dt<=0)
		return;
	
	position += velocity*dt+(acceleration)*0.5*dt*dt;

	acceleration = force_accumulator*inv_mass;

	velocity += acceleration * dt;
	velocity *= pow_real(damping,dt);
	ClearForces();
}

void Particle::SetMass(REAL mass)
{
	inv_mass = (REAL)1.0/mass;
}

REAL Particle::GetMass()
{
	if (inv_mass!=0)
		return (REAL)1.0/inv_mass;
	return 0;
}

bool Particle::HasInfiniteMass()
{
	return inv_mass==0;
}

void Particle::SetInfiniteMass()
{
	inv_mass = 0;
}

void Particle::AddForce(Vector3 & force)
{
	force_accumulator += force;
}

void Particle::ClearForces()
{
	force_accumulator.Clear();
}

REAL Particle::GetInvMass()
{
	return inv_mass;
}