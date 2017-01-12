#include "MassMessage.h"


MassMessage::MassMessage(MESSAGE_TYPE type, AI_TYPES to, Character* from,int SentTo)
:Message(type, to,from)
{
	this->SentTo = SentTo;
}


MassMessage::~MassMessage()
{
}
