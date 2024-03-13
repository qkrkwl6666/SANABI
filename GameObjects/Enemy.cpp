#include "pch.h"
#include "Enemy.h"

Enemy::Enemy(const std::string& name) : SpriteGo(name)
{
	animator = nullptr;
	hp = 0;
	speed = 0.f;
	attackDamage = 0;
	attackSpeed = 0;
}

Enemy::~Enemy()
{
	if (animator != nullptr)
	{
		delete animator;
	}
}


void Enemy::Init()
{
	SpriteGo::Init();

	animator = new Animator();
	animator->SetTarget(&sprite);

}

void Enemy::Reset()
{
	SpriteGo::Reset();
}

void Enemy::Update(float dt)
{
	SpriteGo::Update(dt);

	animator->Update(dt);
}

void Enemy::LateUpdate(float dt)
{
	SpriteGo::LateUpdate(dt);
}

void Enemy::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
