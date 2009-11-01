/*
 * IWidget.cpp
 *
 *  Created on: 29 oct. 2009
 *      Author: Clement
 */

#include "IWidget.h"

namespace CJEngine {

	IWidget::IWidget() {
		_x = 0;
		_y = 0;
		_w = 100;
		_h = 20;
	}

	IWidget::~IWidget() {

	}

	void IWidget::SetSize(int x, int y, int w, int h)
	{
		_x = x;
		_y = y;
		_w = w;
		_h = h;
	}

}
