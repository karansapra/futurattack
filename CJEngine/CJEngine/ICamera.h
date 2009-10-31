/*
 * ICamera.h
 *
 *  Created on: 30 oct. 2009
 *      Author: Clement
 */

#ifndef ICAMERA_H_
#define ICAMERA_H_

namespace CJEngine {

class ICamera {
public:
	ICamera();
	virtual ~ICamera();

	virtual void Apply()=0;
};

}

#endif /* ICAMERA_H_ */
