/*
 * BaseObject.h
 *
 *  Created on: 1 oct. 2009
 *      Author: clement
 */

#ifndef BASEOBJECT_H_
#define BASEOBJECT_H_

#include <string.h>
#include "Constants.h"

class BaseObject {
protected:
	char _name[MAX_NAME_LENGTH];

public:
	BaseObject();
	virtual ~BaseObject();

	void SetName(char * name);
	char * GetName();
	virtual const char * ToString();
};

#endif /* BASEOBJECT_H_ */
