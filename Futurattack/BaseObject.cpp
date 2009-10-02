/*
 * BaseObject.cpp
 *
 *  Created on: 1 oct. 2009
 *      Author: clement
 */

#include "BaseObject.h"

BaseObject::BaseObject() {
	// On rempli de zeros la chaine au depart
	for (int i=0;i<MAX_NAME_LENGTH;i++)
		_name[i]=0x00;
}

BaseObject::~BaseObject() {
	// TODO Auto-generated destructor stub
}

void BaseObject::SetName(char *name)
{
	strcpy(_name,name);
}

char * BaseObject::GetName()
{
	return _name;
}

const char *BaseObject::ToString()
{
	return "BaseObject";
}




