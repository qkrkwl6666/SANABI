#include "pch.h"
#include "SceneTileEditer.h"
#include "TileMap.h"

SceneTileEditer::SceneTileEditer(SceneIds id)
	: Scene(SceneIds::SceneTileEditer)
{

}

void SceneTileEditer::Init()
{
	tileMap = new TileMap("TileMap" , {40.f , 40.f} , {100, 100});
	tileMap->Init();

	AddGo(tileMap);
}

void SceneTileEditer::Update(float dt)
{

}

void SceneTileEditer::Enter()
{

}

void SceneTileEditer::Draw(sf::RenderWindow & window)
{

}
