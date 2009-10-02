/*
 * IViewable.h
 *
 *  Created on: 1 oct. 2009
 *      Author: clement
 */

#ifndef IVIEWABLE_H_
#define IVIEWABLE_H_

#include "IRenderable.h"
#include "Camera.h"

class IViewable: public IRenderable {
protected:
	Camera * _camera;
public:
	IViewable();
	virtual ~IViewable();

	Camera & GetCamera();

	const char * ToString();
};

#endif /* IVIEWABLE_H_ */
