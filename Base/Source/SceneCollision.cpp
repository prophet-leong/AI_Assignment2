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
#include "FILES\MoveTowards.h"
#include "FILES\Attack.h"
#include "FILES\Bribe.h"
#include "FILES\BerserkState.h"
#include "FILES\Idle.h"
_CrtMemState s1;
_CrtMemState s2;
_CrtMemState s3;
SceneCollision::SceneCollision()
{
}

SceneCollision::~SceneCollision()
{
}

void SceneCollision::Init()
{
	srand((unsigned)time(NULL));
	SceneBase::Init();

	pressed = false;

	MessageBoard::GetInstance()->AddEnemy(new Berserker(Vector2(15.f, 0), 10, 2, 1, "Berserker", 1.5f, 1, 3.0f, Color(0.5f, 0.0f, 0.0f)));
	MessageBoard::GetInstance()->AddEnemy(new Knight(Vector2(5.f, 0), 20, 2, 1, "Knight", 1.5f, 1, 3.0f, 2.0f, 7, Color(0.5f, 0.5f, 0.0f)));
	MessageBoard::GetInstance()->AddEnemy(new Archer(Vector2(10, 5.f), 10, 1, 1, 1, "Archer", 4, Color(0.5f, 0.0f, 0.5f)));
	MessageBoard::GetInstance()->AddEnemy(new Mage(Vector2(10, -5.f), 10, 2, 1, 1, "Mage", 5, Color(0.0f, 0.0f, 0.8f)));

	MessageBoard::GetInstance()->AddAlly(new Ally(Vector2(4.f, 0), 20, 4, 2, "Hero", 1.5f, 1.5f, 6.0f, Color(0.0f, 0.8f, 0.0f)));
	_CrtMemCheckpoint(&s1);
	Character* chara = new Ally(Vector2(4.f, 0), 20, 4, 2, "Hero", 1.5f, 1.5f, 6.0f, Color(0.0f, 0.8f, 0.0f));
	//chara->UpdateFSM();
	////chara->SetState(new MoveTowards());
	//chara->Update(0.01);
	//Message* mesa = new Message(MESSAGE_TYPE::FORM_UP, AI_TYPES::ARCHER, chara);
	//delete mesa;
	State* state = new Idle();
	state->update(0.1f, chara, chara);
	delete state;
	delete chara;
	_CrtMemCheckpoint(&s2);
	if (_CrtMemDifference(&s3, &s1, &s2))
		_CrtMemDumpStatistics(&s3);
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

Vector2 TargetedLocation(10, 0);
static float fps;

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

	if ((Application::IsKeyPressed('1') || Application::IsKeyPressed('2') || Application::IsKeyPressed('3') || Application::IsKeyPressed('4') || Application::IsKeyPressed('5')) && !pressed)
	{
		pressed = true;
		if (Application::IsKeyPressed('1'))
		{
			MessageBoard::GetInstance()->AddEnemy((new Berserker(TargetedLocation, 10, 2, 1, "Berserker", 1.5f, 1, 3.0f, Color(0.5f, 0.0f, 0.0f))));
		}
		else if (Application::IsKeyPressed('2'))
		{
			MessageBoard::GetInstance()->AddEnemy(new Knight(TargetedLocation, 20, 2, 1, "Knight", 1.5f, 1, 3.0f, 2.0f, 7, Color(0.5f, 0.5f, 0.0f)));
		}
		else if (Application::IsKeyPressed('3'))
		{
			MessageBoard::GetInstance()->AddEnemy(new Archer(TargetedLocation, 10, 1, 1, 1, "Archer", 4, Color(0.5f, 0.0f, 0.5f)));
		}
		else if (Application::IsKeyPressed('4'))
		{
			MessageBoard::GetInstance()->AddEnemy(new Mage(TargetedLocation, 10, 2, 1, 1, "Mage", 5, Color(0.0f, 0.0f, 0.8f)));
		}
		else if (Application::IsKeyPressed('5'))
		{
			MessageBoard::GetInstance()->AddAlly(new Ally(TargetedLocation, 20, 4, 2, "Hero", 1.5f, 1.5f, 6.0f, Color(0.0f, 0.8f, 0.0f)));
		}
	}
	if (!(Application::IsKeyPressed('1') || Application::IsKeyPressed('2') || Application::IsKeyPressed('3') || Application::IsKeyPressed('4') || Application::IsKeyPressed('5')) && pressed)
	{
		pressed = false;
	}

	if (Application::IsKeyPressed('R'))
	{
		MessageBoard::GetInstance()->ClearAllAllies();
		MessageBoard::GetInstance()->ClearAllEnemies();
		return;
	}
	fps = 1/(float)dt;
	MessageBoard::GetInstance()->UpdateAI(dt);
}


void SceneCollision::RenderGO(Character *go,bool isAlly)
{
	modelStack.PushMatrix();
		modelStack.Translate(go->Position.x, go->Position.y, 0.f);

		modelStack.PushMatrix();
		modelStack.Scale(2, 2, 2);
		if (!isAlly)
		{
			if (go->printName() == "Knight")
				RenderMesh(meshList[GEO_KNIGHT], false);
			else if (go->printName() == "Mage")
				RenderMesh(meshList[GEO_MAGE], false);
			else if (go->printName() == "Archer")
				RenderMesh(meshList[GEO_ARCHER], false);
			else if (go->printName() == "Berserker")
				RenderMesh(meshList[GEO_BERSERK], false);
		}
		else
			RenderMesh(meshList[GEO_BALL], false);
		modelStack.PopMatrix();


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
	projection.SetToOrtho(-20, 20, -10, 10, -10, 10);
	projectionStack.LoadMatrix(projection);
	
	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position, camera.target,camera.up);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	modelStack.PushMatrix();
	modelStack.Translate(TargetedLocation.x, TargetedLocation.y, 0);
	modelStack.Scale(0.1f, 0.1f, 1);
	RenderMesh(meshList[GEO_BALL], false);
	modelStack.PopMatrix();

	float depth = 0.f;
	for (unsigned int i = 0; i < MessageBoard::GetInstance()->GetAllyVector().size(); ++i)
	{
		Character* ally = MessageBoard::GetInstance()->GetAlly(i);
		if (!ally->GetIsDead())
		{
			modelStack.PushMatrix();
			modelStack.Translate(0, 0, depth);
			RenderGO(ally,true);
			modelStack.PopMatrix();
		}
		depth += 0.01f;
	}
	for (unsigned int i = 0; i < MessageBoard::GetInstance()->GetEnemyVector().size(); ++i)
	{
		Enemy* enemy = MessageBoard::GetInstance()->GetEnemy(i);
		if (!enemy->GetIsDead())
		{
			modelStack.PushMatrix();
			modelStack.Translate(0, 0, depth);
			RenderGO(enemy,false);
			modelStack.PopMatrix();
		}
		depth += 0.01f;
	}
	vector<Message*> msg = MessageBoard::GetInstance()->getMessageVector();
	for (unsigned int i = 0; i < msg.size(); ++i)
	{
		if (msg.at(i))
		{
			modelStack.PushMatrix();
			modelStack.Translate(-19.f, 9.f - i, 1.f);
			RenderText(meshList[GEO_TEXT], (&msg)->at(i)->printMessage(), Color(1.f, 1.f, 1.f));
			modelStack.PopMatrix();
		}
	}

	vector<Ally*> ally = MessageBoard::GetInstance()->GetAllyVector();
	vector<Enemy*> enemy = MessageBoard::GetInstance()->GetEnemyVector();

	for (unsigned int i = 0; i < ally.size(); i++)
	{
		if (!ally.at(i)->GetIsDead())
		{
			modelStack.PushMatrix();
			modelStack.Translate(-10.f, 0.f - i, 1.f);
			modelStack.Scale(0.5f, 0.5f, 0.5f);
			RenderText(meshList[GEO_TEXT], ally.at(i)->printInfo(), Color(1.f, 1.f, 1.f));
			modelStack.PopMatrix();
		}
	}
	for (unsigned int i = 0; i < enemy.size(); i++)
	{
		if (!enemy.at(i)->GetIsDead())
		{
			modelStack.PushMatrix();
			modelStack.Translate(-19.f, 0.f - i, 1.f);
			modelStack.Scale(0.5f, 0.5f, 0.5f);
			RenderText(meshList[GEO_TEXT], enemy.at(i)->printInfo(), Color(1.f, 1.f, 1.f));
			modelStack.PopMatrix();
		}
	}
}

void SceneCollision::Exit()
{
	MessageBoard::Destroy();
	SceneBase::Exit();
	//Cleanup GameObjects
	while(m_goList.size() > 0)
	{
		GameObject *go = m_goList.back();
		delete go;
		m_goList.pop_back();
	}
}
