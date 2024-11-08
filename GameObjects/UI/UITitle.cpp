#include "pch.h"
#include "UITitle.h"
#include "UIGo.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "Crosshair.h"

UITitle::UITitle(const std::string& name)
{
	//Init();
}

UITitle::~UITitle()
{

}

void UITitle::Init()
{
	sf::Font& font = RES_MGR_FONT.Get("fonts/NotoSansKR-Regular.otf");

	// *************************로고*************************
	NewSpriteGo("MainBG", "graphics/UI/Spr_MainTitle_LightOn.png");
	sprites["MainBG"]->SetOrigin(Origins::MC);
	sprites["MainBG"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
		0.5f , FRAMEWORK.GetWindowSize().y * 0.5f, });
	sprites["MainBG"]->SetScale({ 1.0f , 1.0f });
	sprites["MainBG"]->sortLayer = 1;

	// *************************배경*************************
	NewSpriteGo("BG", "graphics/UI/UI_MainScene_BG.png");
	sprites["BG"]->SetScale({ 0.7f , 0.7f });
	sprites["BG"]->SetOrigin(Origins::MC);
	sprites["BG"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.5f , FRAMEWORK.GetWindowSize().y * 0.5f, });
	sprites["BG"]->sortLayer = 2;

	// *************************선택*************************
	NewSpriteGo("GameStart", "graphics/UI/UI_MainScene_SelectBox.png");
	sprites["GameStart"]->SetScale({ 1.0f , 1.0f });
	sprites["GameStart"]->SetOrigin(Origins::MC);
	sprites["GameStart"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.89f , FRAMEWORK.GetWindowSize().y * 0.63f, });
	sprites["GameStart"]->sortLayer = 3;

	NewSpriteGo("MapEditer", "graphics/UI/UI_MainScene_SelectBox.png");
	sprites["MapEditer"]->SetScale({ 1.0f , 1.0f });
	sprites["MapEditer"]->SetOrigin(Origins::MC);
	sprites["MapEditer"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.89f , FRAMEWORK.GetWindowSize().y * 0.73f, });
	sprites["MapEditer"]->sortLayer = 3;

	// *************************텍스트************************
	texts.insert({ "GameStart", new TextGo("GameStart") });
	texts.insert({ "MapEditer", new TextGo("MapEditer") });

	texts["GameStart"]->SetFont(font);
	texts["MapEditer"]->SetFont(font);

	texts["GameStart"]->SetString(L"게임 시작");
	texts["MapEditer"]->SetString(L"맵 에디터");

	texts["GameStart"]->SetCharacterSize(40);
	texts["MapEditer"]->SetCharacterSize(40);

	texts["GameStart"]->SetColor(sf::Color::White);
	texts["MapEditer"]->SetColor(sf::Color::White);

	texts["GameStart"]->SetOrigin(Origins::MC);
	texts["MapEditer"]->SetOrigin(Origins::MC);

	texts["GameStart"]->SetPosition({ FRAMEWORK.GetWindowSize().x * 0.82f,
	  FRAMEWORK.GetWindowSize().y * 0.62f });

	texts["MapEditer"]->SetPosition({ FRAMEWORK.GetWindowSize().x * 0.82f ,
		FRAMEWORK.GetWindowSize().y * 0.72f });

	selectBoxs.push_back(sprites["GameStart"]);
	selectBoxs.push_back(sprites["MapEditer"]);

	UiInit();
	ObjectsSort();
}

void UITitle::Release()
{
	GameObject::Release();

	UiDelete();
}

void UITitle::Reset()
{
	GameObject::Reset();
}

void UITitle::Update(float dt)
{
	GameObject::Update(dt);

	HandleMouseSelection();
}

void UITitle::LateUpdate(float dt)
{
	GameObject::LateUpdate(dt);
}

void UITitle::SetCheck(bool c)
{

}

void UITitle::HandleMouseSelection()
{

	for (int i = 0; i < selectBoxs.size(); i++)
	{
		if (selectBoxs[i]->GetGlobalBounds().contains(mouse->GetPosition()))
		{
			selectBoxs[i]->SetTexture("graphics/UI/UI_MainScene_SelectBox_Selected.png");
			if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
			{
				// 씬 전환 타일맵의 크기 및 타일의 크기 전달
				if (i == 0)
				{
					SCENE_MGR.ChangeScene(SceneIds::SceneGame);
				}
				else if (i == 1)
				{
					SCENE_MGR.ChangeScene(SceneIds::SceneTileEditer);
				}

			}
			break;
		}
		else
		{
			selectBoxs[i]->SetTexture("graphics/UI/UI_MainScene_SelectBox.png");
		}
	}
}
