/*
 * IScene.h
 *
 *  Created on: 28 oct. 2009
 *      Author: Clement
 */

#ifndef ISCENE_H_
#define ISCENE_H_

#include "IRenderable.h"

namespace CJEngine {

class IScene : public IRenderable {
public:
	IScene();
	virtual ~IScene();

	virtual void PreRender()=0;
};

}

#endif /* ISCENE_H_ */
