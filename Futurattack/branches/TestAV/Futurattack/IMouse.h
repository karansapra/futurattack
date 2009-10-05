/*
 * IMouse.h
 *
 *  Created on: 1 oct. 2009
 *      Author: clement
 */

#ifndef IMOUSE_H_
#define IMOUSE_H_

#include "BaseObject.h"

class IMouse: public BaseObject {
public:
	IMouse();
	virtual ~IMouse();

	virtual void ButtonPressed(unsigned char button, int x, int y)=0;

	const char * ToString();
};

#endif /* IMOUSE_H_ */
