/*
 * OBJ3DObject.h
 *
 *  Created on: 7 oct. 2009
 *      Author: clement
 */

#ifndef OBJ3DOBJECT_H_
#define OBJ3DOBJECT_H_

#include "I3DObject.h"

class OBJ3DObject: public I3DObject {
public:
	OBJ3DObject();
	virtual ~OBJ3DObject();

	bool Load(char * filename);

	void Render();

	const char * ToString();
};

#endif /* OBJ3DOBJECT_H_ */
