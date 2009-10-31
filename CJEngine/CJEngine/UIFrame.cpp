/*
 * UIFrame.cpp
 *
 *  Created on: 29 oct. 2009
 *      Author: Clement
 */

#include "UIFrame.h"

namespace CJEngine {

	UIFrame::UIFrame() {
		ZeroMemory(&_rect,sizeof(Rect));
	}

	UIFrame::~UIFrame() {

	}

	void UIFrame::Render()
	{
        glBegin(GL_QUADS);
			glColor4f(0.4,0.4,0.4,0.3);
			glVertex3i(_rect.x,_rect.y,1);
			glVertex3i(_rect.x,_rect.y+_rect.h,1);
			glVertex3i(_rect.x+_rect.w,_rect.y+_rect.h,1);
			glVertex3i(_rect.x+_rect.w,_rect.y,1);
        glEnd();
        glBegin(GL_LINE_LOOP);
			glColor4f(0.6,0.8,0.75,0.9);
			glVertex3i(_rect.x,_rect.y,1);
			glVertex3i(_rect.x,_rect.y+_rect.h,1);
			glVertex3i(_rect.x+_rect.w,_rect.y+_rect.h,1);
			glVertex3i(_rect.x+_rect.w,_rect.y,1);
        glEnd();
	}

	void UIFrame::SetDimensions(Rect dimensions)
	{
		_rect = dimensions;
	}

	void UIFrame::SetDimensions(int x, int y, int w, int h)
	{
		_rect.x = x;
		_rect.y = y;
		_rect.w = w;
		_rect.h = h;
	}

	void UIFrame::EventArrived(Event & evt)
	{

	}

}
