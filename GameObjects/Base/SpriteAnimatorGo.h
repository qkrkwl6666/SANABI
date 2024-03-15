#pragma once
#include "SpriteGo.h"

class Animator;

class SpriteAnimatorGo : public SpriteGo
{
protected:
	std::shared_ptr<Animator> animator;

public:
	SpriteAnimatorGo(const std::string& name = "");
	~SpriteAnimatorGo() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	std::shared_ptr<Animator> GetAnimator() { return animator; }
};

