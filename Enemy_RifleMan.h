#pragma once
#include "Enemy.h"

class Animator;
class SpriteGo;
class Player;

class Enemy_RifleMan : public Enemy
{
public:
	enum class Status
	{
		IDLE,
		AIMING,
		SHOOTING,
		STUNED,
		DEAD,
	};

protected:
	Animator* gunAnimator;
	SpriteGo* gun;
	Player* player;

	Status currentStatus;

public:
	Enemy_RifleMan(const std::string& name = "");
	~Enemy_RifleMan() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

