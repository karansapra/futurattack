/*
 * IEventReceiver.h
 *
 *  Created on: 28 oct. 2009
 *      Author: Clement
 */

#ifndef IEVENTRECEIVER_H_
#define IEVENTRECEIVER_H_

namespace CJEngine {

enum EventType {KEYDOWN,MOUSE_LEFT_CLICK,MOUSE_RIGHT_CLICK,MOUSE_MOVE};

struct Event
{
	EventType event_type;

	int mousex;
	int mousey;

	int keycode;
};

class IEventReceiver {
public:
	IEventReceiver();
	virtual ~IEventReceiver();

	virtual void EventArrived(Event & evt)=0;
};

}

#endif /* IEVENTRECEIVER_H_ */
