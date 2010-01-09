#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "types.h"
#include "core.h"
#include "forcegenerator.h"
#include <vector>

struct RigidBody
{
	/*
	World space position
	*/
	Vector3 position;
	
	Vector3 velocity;
	Vector3 rotation;
	Quaternion orientation;
	Quaternion rot;

	Vector3 angular_momentum;

	HomogenousMatrix44 transform;

	RigidBody();
	RigidBody(const Vector3 & initial_position);

	//Accessors
	void SetInertiaTensor(const Matrix33 & inertia_tensor);

	/*
	Zeros the force and torque accumulator
	*/
	void ClearAccumulators();

	/*
	Integration phase
	*/
	void Integrate(REAL dt);

	/*
	Sets the inertia tensor to be a sphere inertia tensor
	*/
	void SetSphereInertiaTensor(REAL radius, REAL mass);
	void SetCubeInertiaTensor(REAL size, REAL mass);
	void SetConeInertiaTensor(REAL base_radius, REAL mass, REAL height);

	/*
	Mass accessors
	*/
	void SetMass(REAL mass);
	REAL GetMass();
	void SetInfiniteMass();
	bool HasInfiniteMass();

	/*
	Adds a force to the rigid body
	The point is relative to the center of mass, but the force
	direction is in world space
	*/
	void AddForceAtBodyPoint(const Vector3 & point, const Vector3 & force);
	void AddForceAtBodyPointAndForceInBodySpace(const Vector3 & point, const Vector3 & force);
	void AddForce(const Vector3 & force);
	void AddTorque(const Vector3 & torque);
	void AddForceAtPoint(const Vector3 & world_point, const Vector3 & force);

	/*
	Changes the drag forces
	*/
	void SetDampingCoefficients(const REAL linear, const REAL rotational);

	Vector3 GetForceAccumulatorValue();
	Vector3 GetTorqueAccumulatorValue();

	/*
	Computes the derived data:
	Every data that is generated from another data
	is transformed here
	*/
	void CalculateDerivedData();


protected:
	/*
	Linear damping
	*/
	REAL damping;
	REAL rotational_damping;

	/*
	Inverse inertia tensor
	*/
	Matrix33 inv_inertia;

	/*
	Inverse inertia tensor in world coordinates
	*/
	Matrix33 inv_inertia_world;

	/*
	Stores the inverse of the body mass
	*/
	REAL inv_mass;
	
	/*
	Force accumulator for each frame
	*/
	Vector3 force_accumulator;
	
	/*
	Torque accumulator for each frame
	*/
	Vector3 torque_accumulator;



	/*
	Performs the transformation of the inertia tensor
	Body to world transform, but only rotation is important
	The translation is not needed
	*/
	Matrix33 TransformInverseInertiaTensor() const;

};










class RigidBodyForceRegistry
{
	struct ForceRegistration
	{
		RigidBody * body;
		IForceGenerator * fgen;
	};
	typedef std::vector<ForceRegistration> Registry;
	Registry registrations;

public:
	void Add(RigidBody & body, IForceGenerator & force_generator);
	void UpdateForces(REAL dt);

};

class World
{
	struct BodyReg
	{
		RigidBody * body;
		BodyReg * next;
	};

	BodyReg * FirstBody;

public:
	RigidBodyForceRegistry fregistry;

	World();
	void StartFrame();
	void RunPhysics(REAL dt);
	void AddBody(RigidBody & body);
};

#endif