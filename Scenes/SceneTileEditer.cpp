#include "pch.h"
#include "SceneTileEditer.h"
#include "TileMap.h"
#include "TileEditer.h"
#include "TextGo.h"

SceneTileEditer::SceneTileEditer(SceneIds id)
	: Scene(SceneIds::SceneTileEditer)
{
	
}

void SceneTileEditer::Init()
{
	
	tileMap = new TileMap("TileMap" , {50.f , 50.f } , {200, 60});
	tileEditer = new TileEditer();

	AddGo(tileMap , Scene::World);
	AddGo(tileEditer, Scene::Ui);

	Scene::Init();
}

void SceneTileEditer::Update(float dt)
{
	Scene::Update(dt);
}

void SceneTileEditer::Release()
{

}

void SceneTileEditer::Enter()
{
	Scene::Enter();

	sf::Font& font = RES_MGR_FONT.Get("fonts/NotoSansKR-Regular.otf");


}

void SceneTileEditer::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
