#pragma once
#include "character.h"
enum AI_TYPES
{
	KNIGHT,
	BERSERKER,
	ARCHER,
	MAGE,
	ALL,
};
enum MESSAGE_TYPE
{
	NEED_HELP,
	FORM_UP,
};
class Message
{
public:
	Message(MESSAGE_TYPE type,AI_TYPES to,Character* from);
	virtual ~Message();

	MESSAGE_TYPE message;
	AI_TYPES to;
	Character* from;
private:

};

