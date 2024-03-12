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
	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

