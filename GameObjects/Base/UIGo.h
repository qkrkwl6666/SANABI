#pragma once
#include "GameObject.h"

class SpriteGo;
class TextGo;

class UIGo : public GameObject
{
protected:
	std::unordered_map<std::string, SpriteGo*> sprites;
	std::unordered_map<std::string, TextGo*> texts;

	std::vector<SpriteGo*> sortSprites;
	std::vector<TextGo*> sortTexts;

	Crosshair* mouse = nullptr;

public:
	UIGo(const std::string& name = "");
	~UIGo() override;
	UIGo(const UIGo&) = delete;
	UIGo(UIGo&&) = delete;
	UIGo& operator=(const UIGo&) = delete;
	UIGo& operator=(UIGo&&) = delete;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;

	void ObjectsSort();
	void Draw(sf::RenderWindow& window) override;
	
	//void SetActive() ;

	virtual void NewSpriteGo(const std::string& name,
		const std::string& textureId);
	virtual void NewTextGo(const std::string& name,
		const sf::Font& font, const std::wstring& str,
		int size, const sf::Color& color);

	virtual void UiInit();
	virtual void UiDraw(sf::RenderWindow& window);
	virtual void UiDelete();
	
	template <typename T>
	static bool compareBySortLayer(T* a, T* b)
	{
		return a->sortLayer < b->sortLayer;
	}
};

