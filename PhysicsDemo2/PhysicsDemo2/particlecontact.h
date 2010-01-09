#ifndef PARTICLECONTACT_H
#define PARTICLECONTACT_H

#include "particle.h"

class ParticleContact
{
public:
	Particle * particles[2];
	REAL restitution;
	REAL penetration;
	Vector3 contact_normal;

	void Resolve(REAL dt);
	REAL CalculateSeparatingVelocity() const;
	void ResolveVelocity(REAL dt);
	void ResolveInterpretation(REAL dt);
};

#endif
