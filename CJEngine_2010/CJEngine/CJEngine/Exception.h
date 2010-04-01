#pragma once

#define EXCEPTION_MESSAGE_SIZE		512

class Exception
{
	char message_[EXCEPTION_MESSAGE_SIZE];

public:
	Exception(void);
	Exception(const char * message);
	Exception(const Exception & exception);

	char * GetMessageA();

	virtual ~Exception(void);
};
