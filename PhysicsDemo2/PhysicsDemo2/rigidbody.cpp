#include "rigidbody.h"

RigidBody::RigidBody()
{
	inv_mass = 1;
	damping = (REAL)0.795;
	rotational_damping = (REAL)0.795;
}

RigidBody::RigidBody(const Vector3 & initial_position)
{
	inv_mass = 1;
	damping = (REAL)0.795;
	rotational_damping = (REAL)0.795;
	position.x = initial_position.x;
	position.y = initial_position.y;
	position.z = initial_position.z;
}

void RigidBody::SetMass(REAL mass)
{
	inv_mass = (REAL)1/mass;
}

void RigidBody::SetSphereInertiaTensor(REAL radius, REAL mass)
{
	SetMass(mass);
	REAL j = 2*mass*radius*radius/5;
	Matrix33 inertia_tensor(j,0,0,0,j,0,0,0,j);
	inv_inertia = inertia_tensor.Inverse();
}

void RigidBody::SetCubeInertiaTensor(REAL size, REAL mass)
{
	SetMass(mass);
	REAL j = ((REAL)1/(REAL)6)*size*size;
	Matrix33 inertia_tensor(j,0,0,0,j,0,0,0,j);
	inv_inertia = inertia_tensor.Inverse();
}

void RigidBody::SetConeInertiaTensor(REAL base_radius, REAL mass, REAL height)
{
	SetMass(mass);
	REAL a = (REAL)3/(REAL)80*mass*height*height+(REAL)3/(REAL)20*mass*base_radius*base_radius;
	REAL b = (REAL)3/(REAL)10*mass*base_radius*base_radius;
	Matrix33 inertia_tensor(a,0,0,0,a,0,0,0,b);
	inv_inertia = inertia_tensor.Inverse();
}

void RigidBody::SetInfiniteMass()
{
	inv_mass = 0;
}

bool RigidBody::HasInfiniteMass()
{
	return (inv_mass==0);
}

void RigidBody::CalculateDerivedData()
{
	orientation.Normalize();
	transform.SetOrientationAndPosition(orientation,position);
	inv_inertia_world = TransformInverseInertiaTensor();
}

void RigidBody::SetInertiaTensor(const Matrix33 & inertia_tensor)
{	
	inv_inertia = inertia_tensor.Inverse();
}

void RigidBody::AddForce(const Vector3 & force)
{
	force_accumulator += force;
}

void RigidBody::AddForceAtBodyPoint(const Vector3 & point, const Vector3 & force)
{
	Vector3 pt_world = transform * point;
	AddForceAtPoint(pt_world,force);
}

void RigidBody::AddForceAtBodyPointAndForceInBodySpace(const Vector3 & point, const Vector3 & force)
{
	Vector3 pt_world = transform * point;
	Vector3 force_world = transform.TransformDirection(force);
	AddForceAtPoint(pt_world,force_world);
}

void RigidBody::AddForceAtPoint(const Vector3 & world_point, const Vector3 & force)
{
	Vector3 pt = world_point - position;
	AddForce(force);
	AddTorque(pt%force);
}

void RigidBody::AddTorque(const Vector3 & torque)
{
	torque_accumulator += torque;
}

void RigidBody::Integrate(REAL dt)
{
	Vector3 acceleration = force_accumulator*inv_mass;
	
	velocity += acceleration*dt;
	
	velocity *= pow_real(damping,dt);
	
	position += velocity*dt;
	
	/*
	ROTATION
	*/
	//////////////////////////

	angular_momentum += torque_accumulator * dt;
	Vector3 inv_I_l = inv_inertia_world * angular_momentum;
	rot = Quaternion(0,inv_I_l.x,inv_I_l.y,inv_I_l.z);
	orientation = orientation + (rot*orientation)*0.5*dt;

	angular_momentum = angular_momentum*pow_real(rotational_damping,dt);

	//////////////////////////

	/*
	Rotation update
	*/
	//Quaternion qrot(0,velocity.x,velocity.y,velocity.z);
	//qrot = qrot * dt;
	//orientation = orientation + qrot * orientation*(REAL)0.5;

	
	
	CalculateDerivedData();

	ClearAccumulators();
}

Vector3 RigidBody::GetForceAccumulatorValue()
{
	return force_accumulator;
}

Vector3 RigidBody::GetTorqueAccumulatorValue()
{
	return torque_accumulator;
}

void RigidBody::ClearAccumulators()
{
	torque_accumulator.Clear();
	force_accumulator.Clear();
}

Matrix33 RigidBody::TransformInverseInertiaTensor() const
{
	Matrix33 rot_tr = transform.ReturnRotationMatrix();
	Matrix33 rot_trT = rot_tr.Transpose();
	return ((rot_tr * inv_inertia.Inverse()) * rot_trT).Inverse();
}	

REAL RigidBody::GetMass()
{
	if (inv_mass==0)
		return 0;
	return (REAL)1/inv_mass;
}

void RigidBody::SetDampingCoefficients(const REAL linear, const REAL rotational)
{
	if (linear>0)
		damping = linear;
	if (rotational>0)
		rotational_damping = rotational;
}












void RigidBodyForceRegistry::Add(RigidBody & body, IForceGenerator & force_generator)
{
	ForceRegistration reg;
	reg.body = &body;
	reg.fgen = &force_generator;
	registrations.push_back(reg);
}

void RigidBodyForceRegistry::UpdateForces(REAL dt)
{
	Registry::iterator i;
	for (i=registrations.begin();i!=registrations.end();i++)
		i->fgen->ForceUpdate(*i->body,dt);
}





World::World()
{
	FirstBody = 0;
}

void World::StartFrame()
{
	BodyReg * reg = FirstBody;
	while (reg)
	{
		reg->body->ClearAccumulators();
		reg->body->CalculateDerivedData();
		reg = reg->next;
	}
}

void World::AddBody(RigidBody & body)
{
	BodyReg * rg = new BodyReg();

	rg->body = &body;
	rg->next = 0;

	if (FirstBody==0)
		FirstBody = rg;
	else
	{
		BodyReg * reg = FirstBody;
		while (reg)
		{
			reg->body->ClearAccumulators();
			reg->body->CalculateDerivedData();
			if (reg->next==0)
			{
				reg->next = rg;
				break;
			}

			reg = reg->next;
		}
	}
}

void World::RunPhysics(REAL dt)
{
	fregistry.UpdateForces(dt);

	BodyReg * reg = FirstBody;
	while (reg)
	{
		reg->body->Integrate(dt);		
		reg = reg->next;
	}
}