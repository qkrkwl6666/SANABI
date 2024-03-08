#include "pch.h"
#include "TileEditer.h"
#include "TileMap.h"
#include "SceneTileEditer.h"
#include "UIGo.h"
#include "Crosshair.h"
#include "TextGo.h"
#include <Windows.h>
#include <commdlg.h> 
#include "rapidjson/document.h"

using namespace rapidjson;

TileEditer::TileEditer(const std::string& name) : UIGo(name)
{
	//Init();
}

TileEditer::~TileEditer()
{

}

void TileEditer::Init()
{
	sf::Font& font = RES_MGR_FONT.Get("fonts/NotoSansKR-Regular.otf");

	sceneTileEditer = dynamic_cast<SceneTileEditer*>
		(SCENE_MGR.GetScene(SceneIds::SceneTileEditer));

	tileMap = sceneTileEditer->GetTitleMap();
	//tilePath = "tileset/Spr_Stage1_Tileset_0.png";
	//tileTexture.loadFromFile("tileset/Spr_Stage1_Tileset_0.png");

	// *************************선택 배경*************************
	NewSpriteGo("SelectBackground", "graphics/UI/UI_Setting_BG.png");
	sprites["SelectBackground"]->SetScale({ 0.1f ,0.3f });
	sprites["SelectBackground"]->SetOrigin(Origins::MC);
	sprites["SelectBackground"]->SetPosition({ 
		FRAMEWORK.GetWindowSize().x * 0.06f, 
		FRAMEWORK.GetWindowSize().y * 0.5f
		});
	sprites["SelectBackground"]->sortLayer = 5;

	// *************************선택 버튼*************************
	NewSpriteGo("TextureSelect", "graphics/UI/UI_WarningWindow_SelectBox.png");
	sprites["TextureSelect"]->SetScale({ 1.0f , 1.0f });
	sprites["TextureSelect"]->SetOrigin(Origins::MC);
	sprites["TextureSelect"]->SetPosition({	
		FRAMEWORK.GetWindowSize().x * 0.06f,
		FRAMEWORK.GetWindowSize().y * 0.37f });
	sprites["TextureSelect"]->sortLayer = 6;

	// ************************선택 텍스트************************
	texts.insert({ "TextureText", new TextGo("TextureText") });
	texts["TextureText"]->SetFont(font);
	texts["TextureText"]->SetString(L"타일 텍스처 선택");
	texts["TextureText"]->SetCharacterSize(30);
	texts["TextureText"]->SetColor(sf::Color::White);
	texts["TextureText"]->SetOrigin(Origins::MC);
	texts["TextureText"]->SetPosition({  
		FRAMEWORK.GetWindowSize().x * 0.06f,
		FRAMEWORK.GetWindowSize().y * 0.365f });
	texts["TextureText"]->sortLayer = 6;

	// ***********************적 생성 버튼************************
	NewSpriteGo("EnemySelect", "graphics/UI/UI_WarningWindow_SelectBox.png");
	sprites["EnemySelect"]->SetScale({ 1.0f , 1.0f });
	sprites["EnemySelect"]->SetOrigin(Origins::MC);
	sprites["EnemySelect"]->SetPosition({
		FRAMEWORK.GetWindowSize().x * 0.06f,
		FRAMEWORK.GetWindowSize().y * 0.44f
		});
	sprites["EnemySelect"]->sortLayer = 6;

	// **********************적 생성 텍스트***********************
	texts.insert({ "EnemyText", new TextGo("TextureText") });
	texts["EnemyText"]->SetFont(font);
	texts["EnemyText"]->SetString(L"적 생성");
	texts["EnemyText"]->SetCharacterSize(30);
	texts["EnemyText"]->SetColor(sf::Color::White);
	texts["EnemyText"]->SetOrigin(Origins::MC);
	texts["EnemyText"]->SetPosition({
		FRAMEWORK.GetWindowSize().x * 0.06f,
		FRAMEWORK.GetWindowSize().y * 0.435f });
	texts["EnemyText"]->sortLayer = 6;

	// *************************저장 버튼*************************
	NewSpriteGo("SaveSelect", "graphics/UI/UI_WarningWindow_SelectBox.png");
	sprites["SaveSelect"]->SetScale({ 1.0f , 1.0f });
	sprites["SaveSelect"]->SetOrigin(Origins::MC);
	sprites["SaveSelect"]->SetPosition({
		FRAMEWORK.GetWindowSize().x * 0.06f,
		FRAMEWORK.GetWindowSize().y * 0.51f
		});
	sprites["SaveSelect"]->sortLayer = 6;

	// ************************저장 텍스트************************
	texts.insert({ "SaveText", new TextGo("SaveText") });
	texts["SaveText"]->SetFont(font);
	texts["SaveText"]->SetString(L"저장");
	texts["SaveText"]->SetCharacterSize(30);
	texts["SaveText"]->SetColor(sf::Color::White);
	texts["SaveText"]->SetOrigin(Origins::MC);
	texts["SaveText"]->SetPosition({
		FRAMEWORK.GetWindowSize().x * 0.06f,
		FRAMEWORK.GetWindowSize().y * 0.505f });
	texts["SaveText"]->sortLayer = 6;

	// ************************타입 버튼************************
	NewSpriteGo("TypeSelect", "graphics/UI/UI_WarningWindow_SelectBox.png");
	sprites["TypeSelect"]->SetScale({ 1.0f , 1.0f });
	sprites["TypeSelect"]->SetOrigin(Origins::MC);
	sprites["TypeSelect"]->SetPosition({
		FRAMEWORK.GetWindowSize().x * 0.06f,
		FRAMEWORK.GetWindowSize().y * 0.58f
		});
	sprites["TypeSelect"]->sortLayer = 6;

	// ************************타입 텍스트************************
	texts.insert({ "TypeText", new TextGo("TypeText") });
	texts["TypeText"]->SetFont(font);
	texts["TypeText"]->SetString(L"타입 설정");
	texts["TypeText"]->SetCharacterSize(30);
	texts["TypeText"]->SetColor(sf::Color::White);
	texts["TypeText"]->SetOrigin(Origins::MC);
	texts["TypeText"]->SetPosition({
		FRAMEWORK.GetWindowSize().x * 0.06f,
		FRAMEWORK.GetWindowSize().y * 0.575f });
	texts["TypeText"]->sortLayer = 6;

	// ************************타입 배경************************
	NewSpriteGo("TypeSelectBackground", "graphics/UI/UI_Setting_BG.png");
	sprites["TypeSelectBackground"]->SetScale({ 0.08f ,0.2f });
	sprites["TypeSelectBackground"]->SetOrigin(Origins::MC);
	sprites["TypeSelectBackground"]->SetPosition({
		FRAMEWORK.GetWindowSize().x * 0.19f,
		FRAMEWORK.GetWindowSize().y * 0.58f
		});
	sprites["TypeSelectBackground"]->sortLayer = 5;

	// ************************타입 WALL************************
	NewSpriteGo("TypeWall", "graphics/UI/UI_WarningWindow_SelectBox.png");
	sprites["TypeWall"]->SetScale({ 0.8f , 0.7f });
	sprites["TypeWall"]->SetOrigin(Origins::MC);
	sprites["TypeWall"]->SetPosition({
		FRAMEWORK.GetWindowSize().x * 0.19f,
		FRAMEWORK.GetWindowSize().y * 0.51f
		});
	sprites["TypeWall"]->sortLayer = 6;

	// ************************타입 PASS************************
	NewSpriteGo("TypePass", "graphics/UI/UI_WarningWindow_SelectBox.png");
	sprites["TypePass"]->SetScale({ 0.8f , 0.71f });
	sprites["TypePass"]->SetOrigin(Origins::MC);
	sprites["TypePass"]->SetPosition({
		FRAMEWORK.GetWindowSize().x * 0.19f,
		FRAMEWORK.GetWindowSize().y * 0.58f
		});
	sprites["TypePass"]->sortLayer = 6;

	// *********************타입 WALLNOGRAB**********************
	NewSpriteGo("TypeWallNoGrab", "graphics/UI/UI_WarningWindow_SelectBox.png");
	sprites["TypeWallNoGrab"]->SetScale({ 0.8f , 0.7f });
	sprites["TypeWallNoGrab"]->SetOrigin(Origins::MC);
	sprites["TypeWallNoGrab"]->SetPosition({
		FRAMEWORK.GetWindowSize().x * 0.19f,
		FRAMEWORK.GetWindowSize().y * 0.65f
		});
	sprites["TypeWallNoGrab"]->sortLayer = 6;

	// ************************타입 WALL 텍스트************************
	texts.insert({ "WallType", new TextGo("WallType") });
	texts["WallType"]->SetFont(font);
	texts["WallType"]->SetString(L"WallType");
	texts["WallType"]->SetCharacterSize(25);
	texts["WallType"]->SetColor(sf::Color::White);
	texts["WallType"]->SetOrigin(Origins::MC);
	texts["WallType"]->SetPosition({
		FRAMEWORK.GetWindowSize().x * 0.19f,
		FRAMEWORK.GetWindowSize().y * 0.51f });
	texts["WallType"]->sortLayer = 6;

	// ************************타입 PASS 텍스트************************
	texts.insert({ "PassType", new TextGo("PassType") });
	texts["PassType"]->SetFont(font);
	texts["PassType"]->SetString(L"PassType");
	texts["PassType"]->SetCharacterSize(25);
	texts["PassType"]->SetColor(sf::Color::White);
	texts["PassType"]->SetOrigin(Origins::MC);
	texts["PassType"]->SetPosition({
		FRAMEWORK.GetWindowSize().x * 0.19f,
		FRAMEWORK.GetWindowSize().y * 0.58f });
	texts["PassType"]->sortLayer = 6;

	// ************************타입 WALLNOGRAB 텍스트************************
	texts.insert({ "WallNoGrabType", new TextGo("WallNoGrabType") });
	texts["WallNoGrabType"]->SetFont(font);
	texts["WallNoGrabType"]->SetString(L"NoGrabType");
	texts["WallNoGrabType"]->SetCharacterSize(25);
	texts["WallNoGrabType"]->SetColor(sf::Color::White);
	texts["WallNoGrabType"]->SetOrigin(Origins::MC);
	texts["WallNoGrabType"]->SetPosition({
		FRAMEWORK.GetWindowSize().x * 0.19f,
		FRAMEWORK.GetWindowSize().y * 0.65f });
	texts["WallNoGrabType"]->sortLayer = 6;

	selectBoxs.push_back(sprites["TextureSelect"]);
	selectBoxs.push_back(sprites["EnemySelect"]);
	selectBoxs.push_back(sprites["SaveSelect"]);
	selectBoxs.push_back(sprites["TypeSelect"]);

	selectTypeBoxs.push_back(sprites["TypeWall"]);
	selectTypeBoxs.push_back(sprites["TypePass"]);
	selectTypeBoxs.push_back(sprites["TypeWallNoGrab"]);

	SetActiveTypeUI(false);

	UIGo::Init();
	ObjectsSort();
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

	screenPos = SCENE_MGR.GetCurrentScene()->UiToScreen((sf::Vector2f)mouse->GetPosition());
	worldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(screenPos);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Middle))
	{
		lastMouseWorldPos = worldPos; // 현재 마우스 위치를 저장합니다.
	}

	// 마우스 휠이 눌린 상태 유지 전에 delta랑 위치가 같지 않을때만
	if (InputMgr::GetMouseButton(sf::Mouse::Middle) && 
		delta != lastMouseWorldPos - worldPos) 
	{
		delta = lastMouseWorldPos - worldPos; // 이동량.

		sceneTileEditer->GetWorldView().move(delta); 
	}

	// 마우스 좌클릭 할때만 Update
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left) && !GetActiveTypeUI())
	{
		TileMouseSelection();
	}

	// UI 배경 마우스 안에서만 Update
	if (sprites["SelectBackground"]->GetGlobalBounds().contains(mouse->GetPosition()))
	{
		HandleMouseSelection();
	}
	// UI Type 배경 안에서만 Update
	if (sprites["TypeSelectBackground"]->GetGlobalBounds().contains
		(mouse->GetPosition()) && GetActiveTypeUI())
	{
		TileTypeMouseSelection();
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
	for (int i = 0; i < selectBoxs.size(); i++)
	{
		if (selectBoxs[i]->GetGlobalBounds().contains(mouse->GetPosition()))
		{
			selectBoxs[i]->SetTexture("graphics/UI/UI_WarningWindow_SelectBox_Selected.png");
			if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
			{
				switch (UIType(i))
				{
					case TileEditer::UIType::TILE_TEXTURE:
						TileSetTexture(OpenFile());
						break;
					case TileEditer::UIType::ENEMY:
						std::cout << "ENEMY" << std::endl;
						break;
					case TileEditer::UIType::SAVE:
						tileMap->SaveTileMap("tilejson/");
						std::cout << "SAVE" << std::endl;
						break;
					case TileEditer::UIType::TYPE:
						SetActiveTypeUI(true);
						std::cout << "TYPE" << std::endl;
						break;
					case TileEditer::UIType::LOAD:
						std::cout << "LOAD" << std::endl;
						break;
				}
			}
			break;
		}
		else
		{
			selectBoxs[i]->SetTexture("graphics/UI/UI_WarningWindow_SelectBox.png");
		}
	}
}

void TileEditer::TileMouseSelection()
{
	screenPos = SCENE_MGR.GetCurrentScene()->UiToScreen((sf::Vector2f)mouse->GetPosition());
	worldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld((sf::Vector2i)screenPos);

	tilePos = sf::Vector2i((worldPos.x / tileMap->GetTileSize().x),
		(worldPos.y / tileMap->GetTileSize().y));

	if (tilePos.x > tileMap->GetMapSize().x - 1 || tilePos.x < 0 ||
		tilePos.y > tileMap->GetMapSize().y - 1 || tilePos.y < 0)
	{
		return;
	}

	tileMap->SetTileTexture(tilePos.y, tilePos.x, tilePath , currentType);
}

void TileEditer::TileSetTexture(const std::wstring& filePath)
{
	tilePath = Utils::WSTRINGToString(filePath);
}

std::wstring TileEditer::OpenFile(const wchar_t* filter, HWND owner)
{
	OPENFILENAMEW ofn; 
	wchar_t fileName[MAX_PATH] = L""; 
	ZeroMemory(&ofn, sizeof(OPENFILENAMEW)); 
	ofn.lStructSize = sizeof(OPENFILENAMEW); 
	ofn.hwndOwner = owner; 
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = L"";

	if (GetOpenFileNameW(&ofn)) 
		return fileName;

	return L"";
}

void TileEditer::TileTypeMouseSelection()
{
	for (int i = 0; i < selectTypeBoxs.size(); i++)
	{
		if (selectTypeBoxs[i]->GetGlobalBounds().contains(mouse->GetPosition()))
		{
			selectTypeBoxs[i]->SetTexture("graphics/UI/UI_WarningWindow_SelectBox_Selected.png");
			if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
			{
				currentType = (TileMap::TileType)i;
				SetActiveTypeUI(false);
			}
			break;
		}
		else
		{
			selectTypeBoxs[i]->SetTexture("graphics/UI/UI_WarningWindow_SelectBox.png");
		}
	}


}

void TileEditer::SetActiveTypeUI(bool active)
{
	isTypeUI = active;

	sprites["TypeWall"]->SetActive(isTypeUI);
	sprites["TypePass"]->SetActive(isTypeUI);
	sprites["TypeWallNoGrab"]->SetActive(isTypeUI);
	sprites["TypeSelectBackground"]->SetActive(isTypeUI);
	texts["WallType"]->SetActive(isTypeUI);
	texts["PassType"]->SetActive(isTypeUI);
	texts["WallNoGrabType"]->SetActive(isTypeUI);
}
