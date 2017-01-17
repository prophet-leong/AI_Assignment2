#include "Message.h"

Message::Message(MESSAGE_TYPE type, AI_TYPES to, Character* from)
{
	this->message = type;
	this->to = to;
	this->from = from;
}

string Message::printMessage()
{
	switch (message)
	{
	case NEED_HELP:
	{
		return "from " + from->printName() + ", HELP REQUESTED";
	}
	case FORM_UP:
	{
		return "from " + from->printName() + ", FORM-UP REQUESTED";
	}
	}
	return "";
}

Message::~Message()
{
}
