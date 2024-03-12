#include "pch.h"
#include "Enemy.h"

void Enemy::Init()
{
	SpriteGo::Init();
}

void Enemy::Reset()
{
	SpriteGo::Reset();
}

void Enemy::Update(float dt)
{
	SpriteGo::Update(dt);
}

void Enemy::LateUpdate(float dt)
{
	SpriteGo::LateUpdate(dt);
}

void Enemy::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
