#include "pch.h"
#include "UIGo.h"
#include "SpriteGo.h"
#include "TextGo.h"

UIGo::UIGo(const std::string& name) : GameObject(name)
{
	Init();
	mouse = FRAMEWORK.GetMouse();
}

UIGo::~UIGo()
{
	UiDelete();
}

void UIGo::Init()
{
	UiInit();
	ObjectsSort();
}

void UIGo::Release()
{
	GameObject::Release();

}

void UIGo::Reset()
{
	GameObject::Reset();
}

void UIGo::Update(float dt)
{
	GameObject::Update(dt);
}

void UIGo::LateUpdate(float dt)
{
	GameObject::LateUpdate(dt);
}

void UIGo::ObjectsSort()
{
	auto it = sprites.begin();
	while (it != sprites.end())
	{
		sortSprites.push_back(it->second);
		it++;
	}

	std::sort(sortSprites.begin(), sortSprites.end(), compareBySortLayer<SpriteGo>);

	auto its = texts.begin();
	while (its != texts.end())
	{
		sortTexts.push_back(its->second);
		its++;
	}

	std::sort(sortTexts.begin(), sortTexts.end(), compareBySortLayer<TextGo>);
}

void UIGo::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);

	UiDraw(window);
}


void UIGo::NewSpriteGo(const std::string& name, const std::string& textureId)
{
	sprites.insert({ name, new SpriteGo(name) });
	sprites[name]->SetTexture(textureId);
}

void UIGo::NewTextGo(const std::string& name, const sf::Font& font, const std::wstring& str, int size, const sf::Color& color)
{
	texts.insert({ name , new TextGo(name) });
	texts[name]->Set(font, str, size, color);
}

void UIGo::UiInit()
{
	for (auto data : sprites)
	{
		data.second->Init();
	}

	for (auto data : texts)
	{
		data.second->Init();
	}
}

void UIGo::UiDraw(sf::RenderWindow& window)
{

	for (auto data : sortSprites)
	{
		if (data->GetActive())
		{
			data->Draw(window);
		}
	}

	for (auto data : texts)
	{
		if (data.second->GetActive())
		{
			data.second->Draw(window);
		}
	}
}

void UIGo::UiDelete()
{
	for (auto data : sprites)
	{
		if (data.second)
		{
			delete data.second;
			data.second = nullptr;
		}

	}

	for (auto data : texts)
	{
		if (data.second)
		{
			delete data.second;
			data.second = nullptr;
		}
	}

	sortSprites.clear();
	sortTexts.clear();
}


