#include "pch.h"
#include "TileMap.h"
#include "Scene.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Enemy_RifleMan.h"
#include "BossMajor.h"
#include "UIGameScene.h"

SceneGame::SceneGame(SceneIds id) : Scene(id)
{

}

void SceneGame::Init()
{
	player = new Player("Player");
	tileMap = new TileMap("TileMap");
	bossMajor = new BossMajor("BossMajor");	
	uiGameScene = new UIGameScene("UIGameScene");

	RES_MGR_SOUND_BUFFER.Get("Audio/BGM_Chap4_Boss_Intro.wav");

	uiGameScene->sortLayer = -2;

	tileMap->sortLayer = 5;

	tileMap->LoadTileMap("tilejson/BossStage_BackUp.json" , 0.f);

	tileMap->sortLayer = -1;

	AddGo(uiGameScene, Scene::World);
	AddGo(tileMap, Scene::World);
	AddGo(bossMajor, Scene::World);
	AddGo(player, Scene::World);


	//AddGo(rifleman, Scene::World);

	for (int i = 0; i < 10; i++)
	{
		enemys.push_back(new Enemy_RifleMan());
	}

	for (auto& data : enemys)
	{
		AddGo(data, Scene::World);
	}

	Scene::Init();

	enemys[0]->SetPosition({1700 , 1620});
	enemys[1]->SetPosition({1650 , 420});
	enemys[2]->SetPosition({2250 , 850});
	enemys[3]->SetPosition({2650 , 350});
	enemys[4]->SetPosition({4650 , 1190});
	enemys[5]->SetPosition({5000 , 1190});
	enemys[6]->SetPosition({4700 , 2080});
	enemys[7]->SetPosition({4900 , 2800});
	enemys[8]->SetPosition({3550 , 2310});
	enemys[9]->SetPosition({3350 , 900});

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

	if (player->GetPosition().x >= 1700 && player->GetPosition().x <= 2200 
		&& player->GetPosition().y >= 2710 && player->GetPosition().y <= 2860)
	{
		player->SetPosition({ 8000.f , 1500.f });
		bossMajor->SetFight();
		SOUND_MGR.PlayBGM("Audio/BGM_Chap4_Boss_Intro.wav");

	}
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

std::vector<Enemy*>* SceneGame::GetEnemys()
{
	return &enemys;
}

BossMajor* SceneGame::GetBossMajor()
{
	return bossMajor;
}
