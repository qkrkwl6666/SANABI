#pragma once
#include "UIGo.h"
#include <Windows.h> // TODO 일단 임시로 사용

class TileMap;
class SceneTileEditer;

class TileEditer : public UIGo
{
	enum class UIType
	{
		TILE_TEXTURE,
		ENEMY,
		SAVE,
		LOAD,
	};

protected:
	// 충돌 처리 컨테이너
	std::vector<SpriteGo*> selectBoxs;
	std::vector<SpriteGo*> checkBoxs;

	SceneTileEditer* sceneTileEditer;
	TileMap* tileMap;

	sf::Vector2f tileSize;
	sf::Vector2i mapSize;

	sf::Texture tileTexture;

	sf::Vector2i screenPos;
	sf::Vector2f worldPos;
	sf::Vector2i tilePos;

public:
	TileEditer(const std::string& name = "");
	~TileEditer() override;
	TileEditer(const TileEditer&) = delete;
	TileEditer(TileEditer&&) = delete;
	TileEditer& operator=(const TileEditer&) = delete;
	TileEditer& operator=(TileEditer&&) = delete;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;

	void SetCheck(bool c);
	void Draw(sf::RenderWindow& window) override;
	void HandleMouseSelection(); // UI 마우스 선택
	void TileMouseSelection(); // 타일 마우스 선택 이벤트
	void TileSetTexture(const std::wstring& filePath);

	std::wstring OpenFile(const wchar_t* filter = L"All Files (*.*)\0*.*\0", HWND owner = NULL);

	// wstring to string
	std::string w2s(const std::wstring& var)
	{
		static std::locale loc("");
		auto& facet = std::use_facet<std::codecvt<wchar_t, char, std::mbstate_t>>(loc);
		return std::wstring_convert<std::remove_reference<decltype(facet)>::type, wchar_t>(&facet).to_bytes(var);
	}

};

