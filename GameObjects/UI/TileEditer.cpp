#include "pch.h"
#include "TileEditer.h"
#include "TileMap.h"
#include "SceneTileEditer.h"
#include "UIGo.h"
#include "Crosshair.h"

TileEditer::TileEditer(const std::string& name) : UIGo(name)
{
	//Init();
}

TileEditer::~TileEditer()
{

}

void TileEditer::Init()
{
	sceneTileEditer = dynamic_cast<SceneTileEditer*>
		(SCENE_MGR.GetScene(SceneIds::SceneTileEditer));

	tileMap = sceneTileEditer->GetTitleMap();
	someTexture.loadFromFile("tileset/Spr_Stage1_Tileset_0.png");
	UIGo::Init();
}

void TileEditer::Release()
{
	UIGo::Release();
}

void TileEditer::Reset()
{
	UIGo::Reset();
}

void TileEditer::Update(float dt)
{
	UIGo::Update(dt);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		HandleMouseSelection();
	}
}

void TileEditer::LateUpdate(float dt)
{
	UIGo::LateUpdate(dt);
}

void TileEditer::SetCheck(bool c)
{

}

void TileEditer::Draw(sf::RenderWindow& window)
{
	UIGo::Draw(window);
}

void TileEditer::HandleMouseSelection()
{
	// UI 에서 월드 위치로 변환

	// ui 좌표 mouse->GetPosition();

	sf::Vector2i ScreenPos = SCENE_MGR.GetCurrentScene()->UiToScreen((sf::Vector2f)mouse->GetPosition());
	sf::Vector2f worldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld((sf::Vector2i)ScreenPos);

	// 타일맵의 타일 크기를 이용하여 타일 좌표 계산
	sf::Vector2i tilePos = sf::Vector2i(static_cast<int>(worldPos.x / tileMap->GetTileSize().x),
		static_cast<int>(worldPos.y / tileMap->GetTileSize().y));

	tileMap->SetTileTexture(tilePos.x, tilePos.y, someTexture);
}
