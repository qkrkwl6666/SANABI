#pragma once
#include "SpriteGo.h"

class Enemy : public SpriteGo
{
protected:
	Animator* animator;
	int hp;
	float speed;
	int attackDamage;
	float attackSpeed;

public:
	Enemy(const std::string& name = "");
	~Enemy() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	virtual void Dead();
	void Draw(sf::RenderWindow& window) override;
};

