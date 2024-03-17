#include "pch.h"
#include "UIGameScene.h"
#include "SpriteGo.h"
#include "Player.h"
#include "SceneGame.h"

UIGameScene::UIGameScene(const std::string& name)
{}

UIGameScene::~UIGameScene()
{}

void UIGameScene::Init()
{
	player = dynamic_cast<SceneGame*>
		(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetPlayer();

	//************************캐릭터 선택 UI***********************

	UiInit();

	ObjectsSort();
}

void UIGameScene::Release()
{
	GameObject::Release();

	UiDelete();
}

void UIGameScene::Reset()
{
	GameObject::Reset();
}

void UIGameScene::Update(float dt)
{
	GameObject::Update(dt);

}

void UIGameScene::LateUpdate(float dt)
{
	GameObject::LateUpdate(dt);
}
