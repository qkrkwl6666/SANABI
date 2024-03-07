#include "pch.h"
#include "TileEditer.h"
#include "TileMap.h"
#include "SceneTileEditer.h"
#include "UIGo.h"
#include "Crosshair.h"
#include "TextGo.h"
#include <Windows.h>
#include <commdlg.h> 

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

	selectBoxs.push_back(sprites["TextureSelect"]);
	selectBoxs.push_back(sprites["EnemySelect"]);
	selectBoxs.push_back(sprites["SaveSelect"]);

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

	// UI 배경 마우스 안에서만 Update
	if (sprites["SelectBackground"]->GetGlobalBounds().contains(mouse->GetPosition()))
	{
		HandleMouseSelection();
	}

	// 마우스 좌클릭 할때만 Update
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		TileMouseSelection();
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
	for (int i = 0; i < 3; i++)
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
						std::cout << "SAVE" << std::endl;
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

	tileMap->SetTileTexture(tilePos.y, tilePos.x, tilePath);
}

void TileEditer::TileSetTexture(const std::wstring& filePath)
{
	tilePath = Utils::WSTRINGToString(filePath);
	//tileTexture.loadFromFile(Utils::WSTRINGToString(filePath));
}

std::wstring TileEditer::OpenFile(const wchar_t* filter, HWND owner)
{
	OPENFILENAMEW ofn; // OPENFILENAME 구조체의 유니코드 버전
	wchar_t fileName[MAX_PATH] = L""; // 파일 이름을 저장할 배열 (유니코드 문자열)
	ZeroMemory(&ofn, sizeof(OPENFILENAMEW)); // 메모리 초기화
	ofn.lStructSize = sizeof(OPENFILENAMEW); // 구조체 크기 설정
	ofn.hwndOwner = owner; // 대화 상자의 부모 윈도우 핸들
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = L"";

	if (GetOpenFileNameW(&ofn)) // 파일 선택 대화 상자를 엽니다. (유니코드 버전 함수 사용)
		return fileName; // 사용자가 파일을 선택하고 "열기"를 클릭하면 파일 경로를 반환합니다.

	return L""; // 사용자가 취소하면 빈 문자열을 반환합니다.
}
