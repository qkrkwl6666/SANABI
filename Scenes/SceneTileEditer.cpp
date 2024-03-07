#include "pch.h"
#include "SceneTileEditer.h"
#include "TileMap.h"
#include "TileEditer.h"

SceneTileEditer::SceneTileEditer(SceneIds id)
	: Scene(SceneIds::SceneTileEditer)
{

}

void SceneTileEditer::Init()
{
	tileMap = new TileMap("TileMap" , {40.f , 40.f} , {100, 100});
	tileEditer = new TileEditer();

	AddGo(tileMap , Scene::World);
	AddGo(tileEditer, Scene::Ui);

	Scene::Init();
}

void SceneTileEditer::Update(float dt)
{
	Scene::Update(dt);
}

void SceneTileEditer::Enter()
{
	Scene::Enter();
}

void SceneTileEditer::Draw(sf::RenderWindow & window)
{
	Scene::Draw(window);
}
