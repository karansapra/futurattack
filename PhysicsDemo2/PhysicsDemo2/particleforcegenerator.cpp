#include "particleforcegenerator.h"

void ParticleForceRegistry::Add(Particle * particle, ParticleForceGenerator * fg)
{
	ParticleForceRegistration pfr;
	pfr.fg = fg;
	pfr.p = particle;
	registrations.push_back(pfr);
}

void ParticleForceRegistry::Clear()
{
	registrations.clear();
}

void ParticleForceRegistry::UpdateForce(REAL dt)
{
	Registry::iterator i;
	for (i=registrations.begin();i!=registrations.end();i++)
		i->fg->UpdateForce(i->p,dt);
}

ParticleGravity::ParticleGravity()
{
}

ParticleGravity::ParticleGravity(const Vector3 & g)
{
	gravity = g;
}

void ParticleGravity::UpdateForce(Particle * p, REAL dt)
{
	if (p->HasInfiniteMass())
		return;

	p->AddForce(gravity*p->GetMass());
}

ParticleSpring::ParticleSpring(Particle * other_particle)
{
	other = other_particle;
	spring_constant = 1.0;
	spring_length = 10.0;
}


void ParticleSpring::UpdateForce(Particle * p, REAL dt)
{
	Vector3 force = p->position - other->position;
	REAL mag = force.Length();
	mag = abs_real(mag-spring_length);
	mag *= spring_constant;
	force.Normalize();
	force *= -mag;
	p->AddForce(force);
}

ParticleAnchoredSpring::ParticleAnchoredSpring()
{
	spring_constant = 1.0;
	spring_length = 10.0;
}

ParticleAnchoredSpring::ParticleAnchoredSpring(Vector3 & anchor_point)
{
	anchor = anchor_point;
	spring_constant = 1.0;
	spring_length = 10.0;
}


void ParticleAnchoredSpring::UpdateForce(Particle * p, REAL dt)
{
	Vector3 force = p->position - anchor;
	REAL mag = force.Length();
	mag = abs_real(mag-spring_length);
	mag *= spring_constant;
	force.Normalize();
	force *= -mag;
	p->AddForce(force);
}