#pragma once
#include "Scene.h"

class Player;
class SpriteGo;
class UITitle;

class SceneTitle : public Scene
{
protected:
	SceneTitle(const SceneTitle&) = delete;
	SceneTitle(SceneTitle&&) = delete;
	SceneTitle& operator=(const SceneTitle&) = delete;
	SceneTitle& operator=(SceneTitle&&) = delete;

	UITitle* uiTitle = nullptr;

public:

	SceneTitle(SceneIds id);
	~SceneTitle() override = default;

	void Init() override;
	void Update(float dt) override;
	void Enter() override;
	void Draw(sf::RenderWindow& window) override;

};

