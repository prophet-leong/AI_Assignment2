
#include "GameObject.h"

GameObject::GameObject(GAMEOBJECT_TYPE typeValue)
	: type(typeValue),
	pos(0,0,0),
	scale(1,1,1),
	active(false)
{
}

GameObject::~GameObject()
{
}