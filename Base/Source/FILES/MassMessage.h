#pragma once
#include "Message.h"
class MassMessage : public Message
{
public:
	MassMessage(MESSAGE_TYPE type, AI_TYPES to, Character* from, int SentTo);
	virtual ~MassMessage();
	int SentTo;
protected:

};

