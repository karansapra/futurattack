#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine()
{

}

void PhysicsEngine::AddBody(SolidBody &body)
{
	bodies.push_back(&body);
}

void PhysicsEngine::Compute(float Te)
{
	for (SolidBodyPtrIterator a=bodies.begin();a<bodies.end();a++)
	{
		//On ne calcule la physique que pour les objets dynamiques
		if ((*a)->Dynamic)
		{
			DynamicObject * dyn = (DynamicObject*)(*a);
			bool collide = false;
			for (SolidBodyPtrIterator b=bodies.begin();b<bodies.end();b++)
			{
				if (*b==*a)
					continue;
				if (dyn->CollisionProcess(**b))
				{
					collide = true;
					if (dyn->CollideCB!=NULL)
						dyn->CollideCB(dyn->Id,(*b)->Id);
				}
			}
			if (collide)
				dyn->Center = dyn->Center_1;

			dyn->Velocity_1 = dyn->Velocity;
			dyn->Center_1 = dyn->Center;

			float m_te = dyn->fMass/Te;
			dyn->Velocity = dyn->CurrentForce+m_te*dyn->Velocity_1;
			dyn->Velocity = dyn->Velocity/(m_te+dyn->fF);			
			dyn->Center = dyn->Center_1+dyn->Velocity*Te;
			int x1 = (int)(dyn->Center.x*10.0f);
			int y1 = (int)(dyn->Center.y*10.0f);
			int x2 = (int)(dyn->Center_1.x*10.0f);
			int y2 = (int)(dyn->Center_1.y*10.0f);
			dyn->isMoving = !(x1==x2 && y1==y2);
		}	
	}
}
