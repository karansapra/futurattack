#include "particlecontact.h"

void ParticleContact::Resolve(REAL dt)
{
	ResolveVelocity(dt);
	ResolveInterpretation(dt);
}

REAL ParticleContact::CalculateSeparatingVelocity() const
{
	Vector3 relative_velocity = particles[0]->velocity;
	if (particles[1])
		relative_velocity -= particles[1]->velocity;
	return relative_velocity * contact_normal;
}

void ParticleContact::ResolveVelocity(REAL dt)
{
	REAL sep_vel = CalculateSeparatingVelocity();

	if (sep_vel>0)
		return;

	REAL new_sep = -sep_vel*restitution;
	REAL dvel = new_sep - sep_vel;

	REAL total_inv_mass = particles[0]->GetInvMass();
	if (particles[1])
		total_inv_mass += particles[1]->GetInvMass();

	if (total_inv_mass<=0)
		return;

	REAL impulse = dvel/total_inv_mass;

	Vector3 impulse_per_mass = contact_normal * impulse;

	particles[0]->velocity += impulse_per_mass*particles[0]->GetInvMass();
	if (particles[1])
		particles[1]->velocity -= impulse_per_mass*particles[1]->GetInvMass();

}

void ParticleContact::ResolveInterpretation(REAL dt)
{
	if (penetration<=0)
		return;

	REAL total_inv_mass = particles[0]->GetInvMass();
	if (particles[1])
		total_inv_mass += particles[1]->GetInvMass();
	
	if (total_inv_mass<=0)
		return;

	Vector3 move_per_mass = contact_normal * (-penetration/total_inv_mass);

	particles[0]->position += move_per_mass*particles[0]->GetInvMass();
	if (particles[1])
		particles[1]->position += move_per_mass*particles[1]->GetInvMass();
}
