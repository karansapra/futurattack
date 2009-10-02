/*
 * IKeyboard.h
 *
 *  Created on: 1 oct. 2009
 *      Author: clement
 */

#ifndef IKEYBOARD_H_
#define IKEYBOARD_H_

#include "BaseObject.h"

class IKeyboard: public BaseObject {
public:
	IKeyboard();
	virtual ~IKeyboard();

	virtual void KeyPressed(char key)=0;

	const char * ToString();
};

#endif /* IKEYBOARD_H_ */
