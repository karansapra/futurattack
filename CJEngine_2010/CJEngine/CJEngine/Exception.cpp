#include "./Exception.h"
#include "./Core.h"

Exception::Exception(void)
{
	strcpy_s(message_,EXCEPTION_MESSAGE_SIZE,"Exception");
}

Exception::Exception(const char * message)
{
	strcpy_s(message_,EXCEPTION_MESSAGE_SIZE,message);
}

Exception::Exception(const Exception & exception)
{
	strcpy_s(message_,EXCEPTION_MESSAGE_SIZE,exception.message_);
}

char * Exception::GetMessageA()
{
	return message_;
}

Exception::~Exception(void)
{
}
