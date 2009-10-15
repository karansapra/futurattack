/*
 * IGameplay.h
 *
 *  Created on: 2 oct. 2009
 *      Author: clement
 */

#ifndef IGAMEPLAY_H_
#define IGAMEPLAY_H_

#include "BaseObject.h"

class IGameplay: public BaseObject {
public:
	IGameplay();
	virtual ~IGameplay();

	virtual void GameplayProcessing()=0;
};

#endif /* IGAMEPLAY_H_ */
