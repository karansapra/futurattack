/*
 * IMaterial.h
 *
 *  Created on: 4 oct. 2009
 *      Author: clement
 */

#ifndef IMATERIAL_H_
#define IMATERIAL_H_

#include "BaseObject.h"

struct RGB
{
	float R;
	float G;
	float B;
};

class IMaterial: public BaseObject {
protected:
	char _material_name[128];

public:
	IMaterial();
	virtual ~IMaterial();

	char * GetMaterialName();

	virtual void Apply()=0;

	RGB ambient;
};

#endif /* IMATERIAL_H_ */
