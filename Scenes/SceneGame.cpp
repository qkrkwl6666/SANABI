#include "pch.h"
#include "TileMap.h"
#include "Scene.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Enemy_RifleMan.h"
#include "BossMajor.h"

SceneGame::SceneGame(SceneIds id) : Scene(id)
{

}

void SceneGame::Init()
{
	player = new Player("Player");
	tileMap = new TileMap("TileMap");
	bossMajor = new BossMajor("BossMajor");

	// rifleman = new Enemy_RifleMan("rifleman");
	// rifleman->SetPosition(player->GetPosition());

	tileMap->LoadTileMap("tilejson/BossStage.json" , 0.f);

	tileMap->sortLayer = -1;

	AddGo(tileMap, Scene::World);
	AddGo(bossMajor, Scene::World);
	AddGo(player, Scene::World);

	//AddGo(rifleman, Scene::World);

	enemys.push_back(new Enemy_RifleMan());
	enemys.push_back(new Enemy_RifleMan());
	enemys.push_back(new Enemy_RifleMan());

	for (auto& data : enemys)
	{
		AddGo(data, Scene::World);
	}

	Scene::Init();

	for (auto& data : enemys)
	{
		data->SetPosition({ 960 + fff , 1613 });
		fff -= 200;
	}

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

	sf::Vector2f viewSpeed = player->GetPosition() - worldView.getCenter();
	worldView.move(viewSpeed * dt * 2.f);
	//worldView.setCenter(Utils::Lerp(worldView.getCenter(), player->GetPosition(), dt));
	if (Utils::Distance(player->GetPosition(), worldView.getCenter()) <= 1.f && InputMgr::GetAxis(Axis::Horizontal) == 0.f && InputMgr::GetAxis(Axis::Vertical) == 0.f)
		worldView.setCenter(player->GetPosition());

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

TileMap* SceneGame::GetTileMap()
{
	if (tileMap != nullptr)
	{
		return tileMap;
	}
	std::cout << "tileMap is nullptr !!" << std::endl;
}

std::list<Enemy*>* SceneGame::GetEnemys()
{
	return &enemys;
}
