/*
 * MenuScene.h
 *
 *  Created on: 28 oct. 2009
 *      Author: Clement
 */

#ifndef MENUSCENE_H_
#define MENUSCENE_H_

#include "CJEngine.h"

using namespace CJEngine;

class MenuScene: public IScene {

public:
	MenuScene();
	virtual ~MenuScene();

	virtual void Render(float time);
	virtual void PreRender();
};


#endif /* MENUSCENE_H_ */
