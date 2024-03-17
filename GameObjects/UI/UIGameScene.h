#pragma once
#include "UIGo.h"

class Player;

class UIGameScene : public UIGo
{
protected:
	Player* player = nullptr;

	float speed = 10.f;
public:
	UIGameScene(const std::string& name = "");
	~UIGameScene() override;
	UIGameScene(const UIGameScene&) = delete;
	UIGameScene(UIGameScene&&) = delete;
	UIGameScene& operator=(const UIGameScene&) = delete;
	UIGameScene& operator=(UIGameScene&&) = delete;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;

};

