#include "pch.h"
#include "TileMap.h"
#include "Scene.h"
#include "SceneGame.h"

SceneGame::SceneGame(SceneIds id) : Scene(id)
	
{

}

void SceneGame::Init()
{

}

void SceneGame::Release()
{
	Scene::Release();
	
}

void SceneGame::Reset()
{
	
}

void SceneGame::Enter()
{
	Scene::Enter();
}

void SceneGame::Exit()
{
	Scene::Exit();
	
}

void SceneGame::Update(float dt)
{

}

void SceneGame::LateUpdate(float dt)
{

}

void SceneGame::FixedUpdate(float dt)
{

}

void SceneGame::DebugUpdate(float dt)
{

}
	
void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
