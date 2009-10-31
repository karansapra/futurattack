/*
 * UIFrame.h
 *
 *  Created on: 29 oct. 2009
 *      Author: Clement
 */

#ifndef UIFRAME_H_
#define UIFRAME_H_

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include "IEventReceiver.h"
#include "IRenderable.h"

namespace CJEngine {

struct Rect
{
	int x;
	int y;
	int w;
	int h;
};

class UIFrame : public IRenderable, public IEventReceiver {
	char *_title;
	Rect _rect;


public:
	UIFrame();
	virtual ~UIFrame();

	virtual void Render();

	void SetTitle(const char * title);
	void SetDimensions(Rect dimensions);
	void SetDimensions(int x, int y, int w, int h);

	void EventArrived(Event & evt);


};

}

#endif /* UIFRAME_H_ */
