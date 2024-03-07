#pragma once
#include "UIGo.h"

class TileMap;
class SceneTileEditer;

class TileEditer : public UIGo
{
protected:
	// 충돌 처리 컨테이너
	std::vector<SpriteGo*> selectBoxs;
	std::vector<SpriteGo*> checkBoxs;

	SceneTileEditer* sceneTileEditer;
	TileMap* tileMap;

	sf::Vector2f tileSize;
	sf::Vector2i mapSize;

	sf::Texture someTexture;

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
	void HandleMouseSelection();
};

