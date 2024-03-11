#pragma once
#include "UIGo.h"
#include "TileMap.h"
#include <Windows.h> // TODO 일단 임시로 사용

class TileMap;
class SceneTileEditer;
class TextGo;

class TileEditer : public UIGo
{
public:
	enum class UIType
	{
		TILE_TEXTURE,
		ENEMY,
		SAVE,
		TYPE,
		LOAD,
	};

protected:
	// 충돌 처리 컨테이너
	std::vector<SpriteGo*> selectBoxs;
	std::vector<SpriteGo*> selectTypeBoxs;
	std::vector<SpriteGo*> checkBoxs;

	SceneTileEditer* sceneTileEditer;
	TileMap* tileMap;

	sf::Vector2f tileSize;
	sf::Vector2i mapSize;

	std::string tilePath = "tileset/Spr_Stage1_Tileset_1.png";

	sf::Vector2i screenPos;
	sf::Vector2f worldPos;
	sf::Vector2i tilePos;
	sf::Vector2f lastMouseWorldPos;
	sf::Vector2f delta;

	bool isTypeUI = false;
	TileMap::TileType currentType = TileMap::TileType::PASS;

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
	void TileTypeMouseSelection();
	void TileSetTexture(const std::string& filePath);

	std::wstring OpenFile(const wchar_t* filter = L"All Files (*.*)\0*.*\0", HWND owner = NULL);

	void SetActiveTypeUI(bool active);
	bool GetActiveTypeUI() const { return isTypeUI ;}

	// 절대 경로 제거 wstring to string
	std::string convertToRelativePath(const std::wstring& absolutePathW);
	
};

