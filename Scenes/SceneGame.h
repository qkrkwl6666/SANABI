#pragma once
#include "Scene.h"

class Player;
class TileMap;
class Enemy_RifleMan;
class Enemy;
class BossMajor;
class UIGameScene;

class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	TileMap* tileMap = nullptr;
	BossMajor* bossMajor = nullptr;
	UIGameScene* uiGameScene = nullptr;


	//Enemy_RifleMan* rifleman = nullptr;

	std::vector<Enemy*> enemys;
	float fff = 20.f;
public:

	SceneGame(SceneIds id);
	~SceneGame() override = default;

	SceneGame(const SceneGame&) = delete;
	SceneGame(SceneGame&&) = delete;
	SceneGame& operator=(const SceneGame&) = delete;
	SceneGame& operator=(SceneGame&&) = delete;

	void Init() override;
	void Release() override;
	void Reset() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void FixedUpdate(float dt) override;
	void DebugUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	Player* GetPlayer();
	TileMap* GetTileMap();
	std::vector<Enemy*>* GetEnemys();
	BossMajor* GetBossMajor();
};

