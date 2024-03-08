#include "pch.h"
#include "SceneTitle.h"
#include "SpriteGo.h"
#include "rapidcsv.h"
#include "UITitle.h"

SceneTitle::SceneTitle(SceneIds id)
	:Scene(id)
{

}

void SceneTitle::Init()
{

	uiTitle = new UITitle("UiTitle");

	AddGo(uiTitle, Scene::Ui);

	Scene::Init();
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
