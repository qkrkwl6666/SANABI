#include "pch.h"
#include "SceneTitle.h"
#include "SpriteGo.h"
#include "rapidcsv.h"
#include "TextGo.h"
#include "Player.h"
#include "AniTest.h"


SceneTitle::SceneTitle(SceneIds id)
	:Scene(id)
{

}

void SceneTitle::Init()
{
	

	aniTest = new AniTest();

	aniTest->Reset();

	Scene::Init();

	//player = new Player();
	//player->Init();
	//player->Reset();
	//animator.Play("data/Idle.csv");
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
