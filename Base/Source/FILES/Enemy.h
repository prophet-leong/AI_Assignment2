#pragma once
#include "Character.h"
#include "States.h"
#include <string>
#include "Message.h"
using std::string;
class Enemy:public Character
{
public:
	Enemy();
	virtual ~Enemy();
	void SetState(State* newState);
	string PrintStateName();
	//setters and getters for the variables
	virtual void SetTarget(Character*Opponent);
	virtual void SetMessage(Message* messsages);
	virtual Message* GetMessage();
	virtual void UpdateMessage(){};
	bool pendingRequest;
	void Exit();
protected:
	Message* messages = 0;
	State* CurrentState = 0;
};

