#include "Message.h"

Message::Message(MESSAGE_TYPE type, AI_TYPES to, Character* from)
{
	this->message = type;
	this->to = to;
	this->from = from;
}

Message::~Message()
{
}
