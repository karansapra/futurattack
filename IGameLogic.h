/*
 * IGameLogic.h
 *
 *  Created on: 28 oct. 2009
 *      Author: Clement
 */

#ifndef IGAMELOGIC_H_
#define IGAMELOGIC_H_

namespace CJEngine {

class IGameLogic {
public:
	IGameLogic();
	virtual ~IGameLogic();

	virtual void ProcessLogic(float sec_time)=0;
};

}

#endif /* IGAMELOGIC_H_ */
