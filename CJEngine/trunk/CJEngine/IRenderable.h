/*
 * IRenderable.h
 *
 *  Created on: 28 oct. 2009
 *      Author: Clement
 */

#ifndef IRENDERABLE_H_
#define IRENDERABLE_H_

namespace CJEngine {

class IRenderable {
public:
	IRenderable();
	virtual ~IRenderable();

	virtual void Render(float time)=0;
};

}

#endif /* IRENDERABLE_H_ */
