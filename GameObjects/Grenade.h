#pragma once
#include "SpriteGo.h"

class Player;
class BossMajor;
class SpriteAnimatorGo;

class Grenade : public SpriteGo
{
protected:
	std::vector<SpriteAnimatorGo*> grenades;

	sf::Vector2f gravity = { 0 , -1 };
	float gravityDt = 0.4f;
	float gravityTime = 0.f;
	float speed = 100.f;

public:
	Player* player = nullptr;
	BossMajor* bossMajor = nullptr;

	Grenade(const std::string& name = "" , BossMajor* bossMajor = nullptr);
	~Grenade() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void GrenadeAttack();
};

