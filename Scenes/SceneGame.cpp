#include "pch.h"
#include "TileMap.h"
#include "Scene.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"

SceneGame::SceneGame(SceneIds id) : Scene(id)
	
{

}

void SceneGame::Init()
{
	player = new Player("Player");
	tileMap = new TileMap("TileMap");

	tileMap->LoadTileMap("tilejson/floor.json");

	tileMap->sortLayer = -1;

	AddGo(tileMap, Scene::World);
	AddGo(player, Scene::World);
	Scene::Init();
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
	player->Reset();
}

void SceneGame::Exit()
{
	Scene::Exit();
	
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

}

void SceneGame::LateUpdate(float dt)
{
	Scene::LateUpdate(dt);
}

void SceneGame::FixedUpdate(float dt)
{
	Scene::FixedUpdate(dt);
}

void SceneGame::DebugUpdate(float dt)
{
	Scene::DebugUpdate(dt);
}
	
void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

Player* SceneGame::GetPlayer()
{
	
	if (player != nullptr)
	{
		return player;
	}
	std::cout << "Player is nullptr !!" << std::endl;
	
}
