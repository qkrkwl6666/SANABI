#include "pch.h"
#include "Enemy_RifleMan.h"
#include "SceneGame.h"
#include "Player.h"
#include "Animator.h"
#include "SpriteGo.h"

Enemy_RifleMan::Enemy_RifleMan(const std::string& name) : Enemy(name)
{

}

Enemy_RifleMan::~Enemy_RifleMan()
{
	if (gunAnimator != nullptr)
	{
		delete gunAnimator;
	}

	if (gun != nullptr)
	{
		delete gun;
	}
}

void Enemy_RifleMan::Init()
{
	Enemy::Init();

	player = dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetPlayer();

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Enemy_RifleMan_Idle.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Enemy_RifleMan_Aiming.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Enemy_RifleMan_Shooting.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Enemy_RifleMan_Ready_Shot.csv"));


	SetScale({ 2.f , 2.f });
	SetOrigin(Origins::MC);
	SetPosition({ 960 , 1613 });

	gun = new SpriteGo();

	gunAnimator = new Animator();
	gunAnimator->SetTarget(gun->GetSprite());

	gunAnimator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Enemy_RifleMan_Arm_Idle.csv"));
	gunAnimator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Enemy_RifleMan_Arm_Aiming.csv"));
	gunAnimator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Enemy_RifleMan_Arm_Shooting.csv"));
	gunAnimator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Enemy_RifleMan_Arm_Ready_Shot.csv"));

	gun->SetScale({ 2.f , 2.f });
	gun->SetPosition(position);
	gun->SetOrigin(Origins::MC);

}

void Enemy_RifleMan::Reset()
{
	Enemy::Reset();
}

void Enemy_RifleMan::Update(float dt)
{
	Enemy::Update(dt);
	gunAnimator->Update(dt);
	gun->SetPosition(position);

	playerPos = player->GetPosition() - gun->GetPosition();

	gun->SetRotation(Utils::Angle(playerPos));
	AnimationIdle();

	switch (currentStatus)
	{
	case Enemy_RifleMan::Status::IDLE:
		if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
		{
			currentStatus = Status::AIMING;
		}
		break;
	case Enemy_RifleMan::Status::AIMING:
		if (isAiming)
		{
			aimingDt += dt;
			if (aimingDt >= aimingDuration)
			{
				aimingDt = 0.f;
				isAiming = false;

				// TODO : Status Shoot À¸·Î ¹Ù²ã¾ßÇÔ
				currentStatus = Status::SHOOTING;
				animator->Play("Enemy_RifleMan_Ready_Shot");
				gunAnimator->Play("Enemy_RifleMan_Arm_Ready_Shot");
			}
			break;
		}
		isAiming = true;
		animator->Play("Enemy_RifleMan_Aiming");
		gunAnimator->Play("Enemy_RifleMan_Arm_Aiming");
		break;

	case Enemy_RifleMan::Status::SHOOTING:
		if (shootingCurrentCount >= shootingMaxCount)
		{
			shootingDt = 0.2f;
			shootingCurrentCount = 0;
			currentStatus = Status::IDLE;
			break;
		}
		shootingDt += dt;

		if (shootingDt >= shootingDuration)
		{
			// ÃÑ¾Ë ¹ß»ç
			animator->Play("Enemy_RifleMan_Shooting");
			gunAnimator->Play("Enemy_RifleMan_Arm_Shooting");
			shootingCurrentCount++;
			shootingDt = 0.f;
		}

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
	gun->Draw(window);

}

void Enemy_RifleMan::AnimationIdle()
{
	if (!animator->IsPlaying())
	{
		animator->Play("Enemy_RifleMan_Idle");
	}

	if (!gunAnimator->IsPlaying())
	{
		gunAnimator->Play("Enemy_RifleMan_Arm_Idle");
	}

}
