#pragma once
#include "SpriteGo.h"

class Animator;
class Player;

class Weapon : public SpriteGo
{
protected:
	Animator* animator = nullptr;
	Player* player = nullptr;

public:
	Weapon(const std::string& name = "");
	~Weapon() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	Animator* GetAnimator();

};

