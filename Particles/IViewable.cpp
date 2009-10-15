/*
 * IViewable.cpp
 *
 *  Created on: 1 oct. 2009
 *      Author: clement
 */

#include "IViewable.h"

IViewable::IViewable() {
	// TODO Auto-generated constructor stub
	_camera = new Camera();
}

IViewable::~IViewable() {
	// TODO Auto-generated destructor stub
}

Camera & IViewable::GetCamera()
{
	return *_camera;
}

const char *IViewable::ToString()
{
	return "IViewable";
}


