#include "pch.h"
#include "SceneTitle.h"
#include "Player.h"
#include "SpriteGo.h"
#include "rapidcsv.h"
#include "UITitle.h"

SceneTitle::SceneTitle(SceneIds id)
	:Scene(id)
{

}

void SceneTitle::Init()
{
	player = new Player("Player");
	uiTitle = new UITitle("UiTitle");

	// player->Init();

	AddGo(player);
	AddGo(uiTitle, Scene::Ui);
	
	Scene::Init();
	player->Reset();


}

void SceneTitle::Update(float dt)
{

	Scene::Update(dt);

}

void SceneTitle::Enter()
{
	Scene::Enter();
}

void SceneTitle::Draw(sf::RenderWindow& window)
{

	Scene::Draw(window);
}

Player* SceneTitle::GetPlayer()
{
	if (player != nullptr)
	{
		return player;
	}

	std::cout << "Player is nullptr !!" << std::endl;
}
