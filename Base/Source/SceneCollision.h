#ifndef SCENE_COLLISION_H
#define SCENE_COLLISION_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"
#include "FILES\/Character.h"

class SceneCollision : public SceneBase
{
public:
	SceneCollision();
	~SceneCollision();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderGO(Character *go);
	GameObject* FetchGO();

protected:
	std::vector<GameObject *> m_goList;
	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	int m_objectCount;
};

#endif