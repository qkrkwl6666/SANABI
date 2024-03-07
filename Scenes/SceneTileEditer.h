#pragma once
#include "Scene.h"

class TileMap;
class TileEditer;

class SceneTileEditer : public Scene
{
protected:
	TileMap* tileMap;
	TileEditer* tileEditer;

public:
	SceneTileEditer(const SceneTileEditer&) = delete;
	SceneTileEditer(SceneTileEditer&&) = delete;
	SceneTileEditer& operator=(const SceneTileEditer&) = delete;
	SceneTileEditer& operator=(SceneTileEditer&&) = delete;

	SceneTileEditer(SceneIds id);
	~SceneTileEditer() override = default;

	TileMap* GetTitleMap() { return tileMap; }

	void Init() override;
	void Update(float dt) override;
	void Enter() override;
	void Draw(sf::RenderWindow& window) override;
	
};

