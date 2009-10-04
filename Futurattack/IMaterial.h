/*
 * IMaterial.h
 *
 *  Created on: 4 oct. 2009
 *      Author: clement
 */

#ifndef IMATERIAL_H_
#define IMATERIAL_H_

#include "BaseObject.h"

class IMaterial: public BaseObject {
public:
	IMaterial();
	virtual ~IMaterial();

	virtual void Apply()=0;
};

#endif /* IMATERIAL_H_ */
