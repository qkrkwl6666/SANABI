#pragma once

#include "UIGo.h"

class UITitle : public UIGo
{
protected:
	// 충돌 처리 컨테이너
	std::vector<SpriteGo*> selectBoxs;
	std::vector<SpriteGo*> checkBoxs;

	bool check = false;

public:
	UITitle(const std::string& name = "");
	~UITitle() override;
	UITitle(const UITitle&) = delete;
	UITitle(UITitle&&) = delete;
	UITitle& operator=(const UITitle&) = delete;
	UITitle& operator=(UITitle&&) = delete;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;

	void SetCheck(bool c);

	void HandleMouseSelection();
	
};

