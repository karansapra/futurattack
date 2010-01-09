#ifndef PARTICLE_H
#define PARTICLE_H

#include "core.h"
#include <vector>


class Particle
{
	/*
	Acceleration
	*/
	Vector3 acceleration;

	/*
	To remove a part of the energy each time we integrate
	*/
	REAL damping;

	/*
	Inverse of the mass, to specify infinite mass
	*/
	REAL inv_mass;

	/*
	Force accumulator
	*/
	Vector3 force_accumulator;



public:
	/*
	Default constructor
	*/
	Particle();

	/*
	To specify the initial position of the particle
	*/
	Particle(const Vector3 &initial_position);

	/*
	To specify the initial position of the particle and its velocity
	*/
	Particle(const Vector3 &initial_position,const Vector3 &initial_velocity);
	
	/*
	Set the mass of the particle
	*/
	void SetMass(REAL mass);

	/*
	Get the mass or 0 if infinite
	*/
	REAL GetMass();

	REAL GetInvMass();

	/*
	To set an inifinite mass for the particle
	No force can move the particle
	*/
	void SetInfiniteMass();

	/*
	Determines if the mass is infinite
	*/
	bool HasInfiniteMass();

	/*
	Add a new force to the particle
	*/
	void AddForce(Vector3 & force);

	/*
	Cancel all forces applied to particle
	*/
	void ClearForces();
	
	/*
	Compute physics of the particle
	*/
	void Integrate(REAL dt);

	/*
	Position of the particle in world space
	*/
	Vector3 position;

	/*
	Velocity
	*/
	Vector3 velocity;

};

#endif
