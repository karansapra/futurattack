/*
 * IWidget.h
 *
 *  Created on: 29 oct. 2009
 *      Author: Clement
 */

#ifndef IWIDGET_H_
#define IWIDGET_H_

#include "IRenderable.h"

namespace CJEngine {

class IWidget : public IRenderable{
	int _x;
	int _y;
	int _w;
	int _h;

public:
	IWidget();
	virtual ~IWidget();

	virtual void SetSize(int x, int y, int w, int h);

	virtual void OnMouseMove(int x, int y)=0;
	virtual void OnClick()=0;
};

}

#endif /* IWIDGET_H_ */
