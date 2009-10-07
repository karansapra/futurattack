/*
 * I3DObject.h
 *
 *  Created on: 4 oct. 2009
 *      Author: clement
 */

#ifndef I3DOBJECT_H_
#define I3DOBJECT_H_

#include <stdio.h>
#include "IRenderable.h"

class I3DObject: public IRenderable {
protected:


public:
	I3DObject();
	virtual ~I3DObject();

	virtual bool Load(char * filename)=0;
};

#endif /* I3DOBJECT_H_ */
