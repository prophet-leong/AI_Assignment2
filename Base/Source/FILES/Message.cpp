#include "Message.h"

Message::Message(MESSAGE_TYPE type, AI_TYPES to, Character* from)
{
	this->message = type;
	this->to = to;
	this->from = from;
}

string Message::printMessage()
{
	switch (to)
	{
	case KNIGHT:
		sentTo = "KNIGHT";
		break;
	case BERSERKER:
		sentTo = "BERSERKER";
		break;
	case ARCHER:
		sentTo = "ARCHER";
		break;
	case MAGE:
		sentTo = "MAGE";
		break;
	case ALL:
		sentTo = "ALL";
		break;
	default:
		break;
	}

	switch (message)
	{
	case NEED_HELP:
	{
		return "From " + from->printName() + " to " + sentTo + ": Need Help!";
	}
	case FORM_UP:
	{
		return "From " + from->printName() + " to " + sentTo + ": Gather!";
	}
	}
	return "";
}

Message::~Message()
{
}
