#pragma once
#include "SpriteGo.h"

class Animator;
class Weapon;

class Player : public SpriteGo
{
protected:
	Animator* animator = nullptr;
	Animator* weaponAnimator = nullptr;
	Weapon* weapon;

	sf::Vector2f WeaponPoint;
	float gravity = 800.f;
	float speed = 1000.f;
	sf::Vector2f velocity; // 속도 // 방향 * speed
	bool isGround = true;
	bool Falling = false;

public:
	Player(const std::string& name = "");
	~Player() override;

	// static void TestStatic();
	// void TestInstance();

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void PlayerAnimationPlay(const std::string& player,
		const std::string& weapon, bool clearQueue = true);

	void PlayerFalling();
	void PlayerJumping();
	void Delete();

};


