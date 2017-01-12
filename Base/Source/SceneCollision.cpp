#include "SceneCollision.h"
#include "GL\glew.h"
#include "Application.h"

#include "FILES/Archer.h"
#include "FILES/Berserker.h"
#include "FILES/Knight.h"
#include "FILES/Mage.h"
#include "FILES/Ally.h"
#include "FILES/MessageBoard.h"
#include <sstream>
#include <time.h>
#include <fstream>

SceneCollision::SceneCollision()
{
}

SceneCollision::~SceneCollision()
{
}

void SceneCollision::Init()
{
	SceneBase::Init();
	MessageBoard::GetInstance()->AddEnemy(new Berserker(Vector2(5.f, 0), 10, 2, 1, "Berserker", 1.5f, 1, 3.0f, Color(0.5f, 0.0f, 0.0f)));
	MessageBoard::GetInstance()->AddEnemy(new Knight(Vector2(-5.f, 0), 20, 2, 1, "Knight", 1.5f, 1, 3.0f, 2.0f, 7, Color(0.5f, 0.5f, 0.0f)));
	MessageBoard::GetInstance()->AddEnemy(new Archer(Vector2(0, 5.f), 10, 1, 1, 1, "Archer", 4, Color(0.5f, 0.0f, 0.5f)));
	MessageBoard::GetInstance()->AddEnemy(new Mage(Vector2(0, -5.f), 10, 2, 1, 1, "Mage", 5, Color(0.0f, 0.0f, 0.8f)));
	MessageBoard::GetInstance()->AddAlly(new Ally(Vector2(0, 0), 20, 4, 2, "Hero", 1.5f, 1.5f, 6.0f, Color(0.0f, 0.8f, 0.0f)));
}

GameObject* SceneCollision::FetchGO()
{
	m_objectCount++;
	for (std::vector<GameObject*>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = *it;
		if (!go->active)
		{
			go->active = true;
			return go;
		}
	}
	for (int i = 0; i < 10; ++i)
	{
		GameObject *newgo = new GameObject(GameObject::GO_BALL);
		m_goList.push_back(newgo);
	}
	GameObject *newgo = *(m_goList.end() - 1);
	newgo->active = true;
	return newgo;
}

Vector2 TargetedLocation(0, 0);

void SceneCollision::Update(double dt)
{
	SceneBase::Update(dt);

	if (Application::IsKeyPressed('W'))
	{
		TargetedLocation.y += 8 * (float)dt;
	}
	if (Application::IsKeyPressed('S'))
	{
		TargetedLocation.y -= 8 * (float)dt;
	}
	if (Application::IsKeyPressed('A'))
	{
		TargetedLocation.x -= 8 * (float)dt;
	}
	if (Application::IsKeyPressed('D'))
	{
		TargetedLocation.x += 8 * (float)dt;
	}

	if (Application::IsKeyPressed('1'))
	{
		MessageBoard::GetInstance()->AddEnemy((new Berserker(TargetedLocation, 10, 2, 1, "Berserker", 1.5f, 1, 3.0f, Color(0.5f, 0.0f, 0.0f))));
	}
	if (Application::IsKeyPressed('2'))
	{
		MessageBoard::GetInstance()->AddEnemy(new Knight(TargetedLocation, 20, 2, 1, "Knight", 1.5f, 1, 3.0f, 2.0f, 7, Color(0.5f, 0.5f, 0.0f)));
	}
	if (Application::IsKeyPressed('3'))
	{
		MessageBoard::GetInstance()->AddEnemy(new Archer(TargetedLocation, 10, 1, 1, 1, "Archer", 4, Color(0.5f, 0.0f, 0.5f)));
	}
	if (Application::IsKeyPressed('4'))
	{
		MessageBoard::GetInstance()->AddEnemy(new Mage(TargetedLocation, 10, 2, 1, 1, "Mage", 5, Color(0.0f, 0.0f, 0.8f)));
	}
	if (Application::IsKeyPressed('5'))
	{
		MessageBoard::GetInstance()->AddAlly(new Ally(TargetedLocation, 20, 4, 2, "Hero", 1.5f, 1.5f, 6.0f, Color(0.0f, 0.8f, 0.0f)));
	}

	if (Application::IsKeyPressed('R'))
	{
		MessageBoard::GetInstance()->ClearAllAllies();
		MessageBoard::GetInstance()->ClearAllEnemies();
	}
	MessageBoard::GetInstance()->UpdateAI(dt);
}

void SceneCollision::RenderGO(Character *go)
{
	modelStack.PushMatrix();
		modelStack.Translate(go->Position.x, go->Position.y, 0.f);
		RenderMesh(meshList[GEO_BALL], false);

		modelStack.PushMatrix();
			//might need to scale here?
			modelStack.PushMatrix();
				modelStack.Scale(go->GetAttackingRange(), go->GetAttackingRange(), 0);
				RenderMesh(meshList[GEO_ATTACKRING], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
				modelStack.Scale(go->GetDetectionRange(), go->GetDetectionRange(), 0);
				RenderMesh(meshList[GEO_DETECTIONRING], false);
			modelStack.PopMatrix();

		modelStack.PopMatrix();

		modelStack.PushMatrix();
			modelStack.Translate(0, 1.f, 1.f);
			modelStack.Scale(((float)go->health / (float)go->maxHealth) * 1.5f, 0.25f, 1.f);
			RenderMesh(meshList[GEO_HP_BAR], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
			modelStack.Translate(0, -0.5f, 1.f);
			RenderText(meshList[GEO_TEXT], go->KIMINONAWA(), Color(0.5f, 0.5f, 0.5f));
		modelStack.PopMatrix();

	modelStack.PopMatrix();
}

void SceneCollision::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	// Projection matrix : Orthographic Projection
	//we test 10 x 10
	Mtx44 projection;
	projection.SetToOrtho(-10, 10, -10, 10, -10, 10);
	projectionStack.LoadMatrix(projection);
	
	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position, camera.target,camera.up);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	float depth = 0.f;
	for (unsigned int i = 0; i < MessageBoard::GetInstance()->GetAllyVector().size(); ++i)
	{
		Ally* ally = MessageBoard::GetInstance()->GetAlly(i);
		if (!ally->GetIsDead())
		{
			modelStack.PushMatrix();
			modelStack.Translate(0, 0, depth);
			RenderGO(ally);
			modelStack.PopMatrix();
		}
		depth += 0.01f;
	}
	for (unsigned int i = 0; i < MessageBoard::GetInstance()->GetEnemyVector().size(); ++i)
	{
		Enemy* enemy = MessageBoard::GetInstance()->GetEnemy(i);
		if (enemy)
		{
			modelStack.PushMatrix();
			modelStack.Translate(0, 0, depth);
			RenderGO(enemy);
			modelStack.PopMatrix();
		}
		depth += 0.01f;
	}
}

void SceneCollision::Exit()
{
	SceneBase::Exit();
	//Cleanup GameObjects
	while(m_goList.size() > 0)
	{
		GameObject *go = m_goList.back();
		delete go;
		m_goList.pop_back();
	}
}
