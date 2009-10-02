/*
 * IRenderable.h
 *
 *  Created on: 1 oct. 2009
 *      Author: clement
 */

#ifndef IRENDERABLE_H_
#define IRENDERABLE_H_

#include "BaseObject.h"

class IRenderable: public BaseObject {
public:
	IRenderable();
	virtual ~IRenderable();

	virtual void Render()=0;
	virtual void PreRender();

	const char * ToString();
};

#endif /* IRENDERABLE_H_ */
