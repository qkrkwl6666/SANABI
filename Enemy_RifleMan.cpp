#include "pch.h"
#include "Enemy_RifleMan.h"
#include "SceneGame.h"
#include "Player.h"
#include "Animator.h"

Enemy_RifleMan::Enemy_RifleMan(const std::string& name) : Enemy(name)
{

}

Enemy_RifleMan::~Enemy_RifleMan()
{
	if (gunAnimator != nullptr)
	{
		delete gunAnimator;
	}
}

void Enemy_RifleMan::Init()
{
	Enemy::Init();

	player = dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetPlayer();

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Enemy_RifleMan_Idle.csv"));

	SetPosition({ 960 , 1613 });
	SetScale({ 2.f , 2.f });
	SetOrigin(Origins::MC);
}

void Enemy_RifleMan::Reset()
{
	Enemy::Reset();
}

void Enemy_RifleMan::Update(float dt)
{
	Enemy::Update(dt);

	if (!animator->IsPlaying())
	{
		animator->Play("Enemy_RifleMan_Idle");
	}

	switch (currentStatus)
	{
	case Enemy_RifleMan::Status::IDLE:

		break;
	case Enemy_RifleMan::Status::AIMING:

		break;
	case Enemy_RifleMan::Status::SHOOTING:

		break;
	case Enemy_RifleMan::Status::STUNED:

		break;
	case Enemy_RifleMan::Status::DEAD:

		break;
	default:
		break;
	}
}

void Enemy_RifleMan::LateUpdate(float dt)
{
	Enemy::LateUpdate(dt);
}

void Enemy_RifleMan::Draw(sf::RenderWindow& window)
{
	Enemy::Draw(window);
}
