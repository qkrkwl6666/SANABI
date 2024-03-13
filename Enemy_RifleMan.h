#pragma once
#include "Enemy.h"

class Animator;
class SpriteGo;
class Player;
class Bullet;

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

	sf::Vector2f gunPoint;
	sf::Vector2f playerPos;
	sf::Vector2f playerBulletPos;

	Status currentStatus;

	std::vector<Bullet*> bullets;

	

	bool isAiming = false;
	bool isShooting = false;
	float aimingDt = 0.f;
	float aimingDuration = 1.5f;

	float shootingDt = 0.f;
	float shootingDuration = 0.01f;
	int shootingMaxCount = 3; // ÃÑ¾Ë ¹ß»ç °¹¼ö
	int shootingCurrentCount = 0;

public:
	Enemy_RifleMan(const std::string& name = "");
	~Enemy_RifleMan() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void AnimationIdle();
};

