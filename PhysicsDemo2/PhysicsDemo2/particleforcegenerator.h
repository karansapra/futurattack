#ifndef PARTICLEFORCEGENERATOR_H
#define PARTICLEFORCEGENERATOR_H

#include <vector>
#include "core.h"
#include "types.h"
#include "particle.h"

class ParticleForceGenerator
{
public:
	virtual void UpdateForce(Particle * p, REAL dt)=0;
};

class ParticleForceRegistry
{
	struct ParticleForceRegistration
	{
		Particle *p;
		ParticleForceGenerator *fg;
	};

	typedef std::vector<ParticleForceRegistration> Registry;

	Registry registrations;

public:
	/*
	Registers a force generator to the given particle
	*/
	void Add(Particle * particle, ParticleForceGenerator * fg);

	/*
	Clears all registrations in the registry
	*/
	void Clear();

	/*
	Update all force generators for their particles
	*/
	void UpdateForce(REAL dt);
};


class ParticleGravity : public ParticleForceGenerator
{	
public:
	Vector3 gravity;

	ParticleGravity();
	ParticleGravity(const Vector3 & g);

	virtual void UpdateForce(Particle * p, REAL dt);
};


class ParticleSpring : public ParticleForceGenerator
{
public:
	REAL spring_constant;
	REAL spring_length;
	Particle * other;

	ParticleSpring(Particle * other_particle);
	virtual void UpdateForce(Particle * p, REAL dt);
};

class ParticleAnchoredSpring : public ParticleForceGenerator
{
public:
	REAL spring_constant;
	REAL spring_length;
	Vector3 anchor;

	ParticleAnchoredSpring();
	ParticleAnchoredSpring(Vector3 & anchor_point);
	virtual void UpdateForce(Particle * p, REAL dt);
};

#endif
