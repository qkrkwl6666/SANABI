#include "pch.h"
#include "Enemy_Defender.h"

void Enemy_Defender::Init()
{
	animator = new Animator();
	animator->SetTarget(&sprite);

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Idle.csv"));

	SetOrigin(Origins::MC);
}

void Enemy_Defender::Reset()
{

}

void Enemy_Defender::Update(float dt)
{
	Enemy::Update(dt);
}

void Enemy_Defender::LateUpdate(float dt)
{
	Enemy::LateUpdate(dt);
}

void Enemy_Defender::Draw(sf::RenderWindow& window)
{
	Enemy::Draw(window);
}
