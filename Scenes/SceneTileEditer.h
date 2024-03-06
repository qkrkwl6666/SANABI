#pragma once
#include "Scene.h"

class TileMap;

class SceneTileEditer : public Scene
{
protected:
	TileMap* tileMap;

public:
	SceneTileEditer(const SceneTileEditer&) = delete;
	SceneTileEditer(SceneTileEditer&&) = delete;
	SceneTileEditer& operator=(const SceneTileEditer&) = delete;
	SceneTileEditer& operator=(SceneTileEditer&&) = delete;

	SceneTileEditer(SceneIds id);
	~SceneTileEditer() override = default;

	void Init() override;
	void Update(float dt) override;
	void Enter() override;
	void Draw(sf::RenderWindow& window) override;
	
};
