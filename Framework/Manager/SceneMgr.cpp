#include "pch.h"
#include "SceneMgr.h"
#include "SceneGame.h"
#include "SceneTitle.h"
#include "SceneTileEditer.h"

SceneMgr::~SceneMgr()
{
	Release();
}

void SceneMgr::Init()
{
	Release();

	scenes.push_back(new SceneTitle(SceneIds::SceneTitle));
	scenes.push_back(new SceneGame(SceneIds::SceneGame));
	scenes.push_back(new SceneTileEditer(SceneIds::SceneTileEditer));

	for (auto scene : scenes)
	{
		scene->Init();
	}

	currentScene = startScene;
	scenes[(int)currentScene]->Enter();
}

void SceneMgr::Release()
{
	for (auto scene : scenes)
	{
		scene->Release();
		delete scene;
	}
	scenes.clear();
}

void SceneMgr::ChangeScene(SceneIds id)
{
	// TO-DO: 모든 게임 오브젝트 업데이트 끝난 후에 씬 전환 되도록

	nextScene = id;
}

bool SceneMgr::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::F5))
	{
		SCENE_MGR.ChangeScene(SceneIds::SceneTitle);
	}

	scenes[(int)currentScene]->Update(dt);

	if (nextScene != SceneIds::None)
	{
		scenes[(int)currentScene]->Exit();
		currentScene = nextScene;
		scenes[(int)currentScene]->Enter();

		nextScene = SceneIds::None;

		return false;
	}

	return true;
}

void SceneMgr::LateUpdate(float dt)
{
	scenes[(int)currentScene]->LateUpdate(dt);
}

void SceneMgr::FixedUpdate(float dt)
{
	scenes[(int)currentScene]->FixedUpdate(dt);
}

void SceneMgr::DebugUpdate(float dt)
{
	scenes[(int)currentScene]->DebugUpdate(dt);
}

void SceneMgr::Draw(sf::RenderWindow& window)
{
	scenes[(int)currentScene]->Draw(window);
}

void SceneMgr::DebugDraw(sf::RenderWindow& window)
{
	scenes[(int)currentScene]->DebugDraw(window);
}
