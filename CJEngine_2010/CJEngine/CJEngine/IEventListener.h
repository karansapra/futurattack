#pragma once

struct Event
{
	unsigned char keystate[256];
};

class IEventListener
{
public:
	virtual void OnEvent(const Event & evt) = 0;
};