/*
 * StandardMaterial.h
 *
 *  Created on: 13 oct. 2009
 *      Author: clement
 */

#ifndef STANDARDMATERIAL_H_
#define STANDARDMATERIAL_H_

#include <stdio.h>
#include <GL/freeglut.h>
#include "IMaterial.h"

class StandardMaterial: public IMaterial {

public:
	StandardMaterial(const char * material_name);
	virtual ~StandardMaterial();

	void Apply();
};

#endif /* STANDARDMATERIAL_H_ */
