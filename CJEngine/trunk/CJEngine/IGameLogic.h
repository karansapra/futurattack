/*
 * IGameLogic.h
 *
 *  Created on: 28 oct. 2009
 *      Author: Clement
 */

#ifndef IGAMELOGIC_H_
#define IGAMELOGIC_H_

#include "IEventReceiver.h"

namespace CJEngine {

class IGameLogic: public IEventReceiver {
public:
	IGameLogic();
	virtual ~IGameLogic();

	virtual void RenderPass(float sec_time)=0;
};

}

#endif /* IGAMELOGIC_H_ */
