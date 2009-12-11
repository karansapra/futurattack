#pragma once

#include <vector>
#include "PhysicsObjects.h"

typedef std::vector<SolidBody*>::iterator SolidBodyPtrIterator;

class PhysicsEngine
{
	std::vector<SolidBody*> bodies;

public:
	PhysicsEngine();
	void AddBody(SolidBody &body);
	void Compute(float Te=0.1f);
};