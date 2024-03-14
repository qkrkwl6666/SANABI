#include "pch.h"
#include "Enemy_RifleMan.h"
#include "SceneGame.h"
#include "Player.h"
#include "Animator.h"
#include "SpriteGo.h"
#include "Bullet.h"

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
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Enemy_RifleMan_Dead.csv"));

	SetTexture("graphics/Enemy/RifleMan/Spr_ENE_Rifleman_Ready2Shot.png");

	SetScale({ 2.f , 2.f });
	SetOrigin(Origins::MC);
	SetPosition({ 960 , 1613 });

	gunPoint = { 5 , -10 };

	gun = new SpriteGo();

	gun->SetTexture("graphics/Enemy/RifleMan/Spr_ENE_RiflemanArm_Ready2Shot.png");

	gun->SetScale({ 2.f , 2.f });
	gun->SetOrigin(Origins::BC);
	gun->SetPosition(GetPosition() + gunPoint);

	gunAnimator = new Animator();
	gunAnimator->SetTarget(gun->GetSprite());

	gunAnimator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Enemy_RifleMan_Arm_Idle.csv"));
	gunAnimator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Enemy_RifleMan_Arm_Aiming.csv"));
	gunAnimator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Enemy_RifleMan_Arm_Shooting.csv"));
	gunAnimator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Enemy_RifleMan_Arm_Ready_Shot.csv"));

	bullets.resize(12, new Bullet());
}

void Enemy_RifleMan::Reset()
{
	Enemy::Reset();
}

void Enemy_RifleMan::Update(float dt)
{
	Enemy::Update(dt);
	gunAnimator->Update(dt);
	
	//std::cout << isShooting << std::endl;
	//std::cout << shootingCurrentCount << std::endl;
	//std::cout << shootingDt << std::endl;

	for (auto& data : bullets)
	{
		if (data->GetActive())
		{
			data->Update(dt);
		}

	}
	playerPos = player->GetPosition() - gun->GetPosition();

	if (Utils::Angle(playerPos) >= -90 && Utils::Angle(playerPos) <= 90)
	{
		gunPoint = { 5.f , -10.f };
		SetFlipX(false);
		gun->SetFlipX(false);
		gun->SetRotation(Utils::Angle(playerPos));
	}
	else if (Utils::Angle(playerPos) <= -90 && Utils::Angle(playerPos) <= 90)
	{
		gunPoint = { -5.f , -10.f };
		SetFlipX(true);
		gun->SetFlipX(true);
		gun->SetRotation(-180 + Utils::Angle(playerPos));
	}

	if (!isShooting)
	{
		gun->SetPosition(GetPosition() + gunPoint);
	}

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

				currentStatus = Status::SHOOTING;
				animator->Play("Enemy_RifleMan_Ready_Shot");
				gunAnimator->Play("Enemy_RifleMan_Arm_Ready_Shot");
				playerBulletPos = Utils::GetNormalize(player->GetPosition() - GetPosition());
			}
			break;
		}
		isAiming = true;
		animator->Play("Enemy_RifleMan_Aiming");
		gunAnimator->Play("Enemy_RifleMan_Arm_Aiming");
		break;

	case Enemy_RifleMan::Status::SHOOTING:
		isShooting = true;
		shootingDt += dt;
		gun->SetRotation(Utils::Angle(playerBulletPos));

		if (Utils::Angle(playerBulletPos) <= -90 && Utils::Angle(playerBulletPos) <= 90)
		{
			SetFlipX(true);
			gun->SetFlipX(true);
			gun->SetRotation(-180 + Utils::Angle(playerBulletPos));
		}

		if (shootingCurrentCount >= shootingMaxCount)
		{
			shootingDt = 0.2f;
			shootingCurrentCount = 0;
			currentStatus = Status::IDLE;
			isShooting = false;
			break;
		}

		if (shootingDt >= shootingDuration)
		{
			// 총알 발사
			// TODO : 총알 로직 수정해야함
			animator->Play("Enemy_RifleMan_Shooting");
			gunAnimator->Play("Enemy_RifleMan_Arm_Shooting");
			auto it = bullets.begin();
			while (it != bullets.end())
			{
				Bullet* bullet = dynamic_cast<Bullet*>(*it);
				if (!bullet->GetActive())
				{
					bullet->Shooting(playerBulletPos, this);
					shootingCurrentCount++;
					shootingDt = 0.f;
					break;
				}
				else
				{
					it++;
				}
			}
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

	for (auto& data : bullets)
	{
		if (data->GetActive())
		{
			data->Draw(window);
		}
	}
}

void Enemy_RifleMan::Dead()
{
	animator->Play("Enemy_RifleMan_Dead");
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
