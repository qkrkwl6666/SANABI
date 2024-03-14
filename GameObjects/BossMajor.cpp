#include "pch.h"
#include "BossMajor.h"
#include "Frail.h"
#include "Player.h"
#include "SceneGame.h"

BossMajor::BossMajor(const std::string& name) : Enemy(name)
{

}

BossMajor::~BossMajor()
{

}

void BossMajor::Init()
{
	Enemy::Init();
	player = dynamic_cast<SceneGame*>
		(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetPlayer();

	frail = new Frail("Frail" , this);

	frialAnimator = frail->GetAnimator();

	SetTexture("graphics/Enemy/Boss_Major/Spr_BOSS_Major_Idle.png");
	SetScale({ 2.f , 2.f });
	SetOrigin(Origins::BC);

	animator->SetTarget(&sprite);
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Boss/Spr_BOSS_Major_Idle.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Boss/Spr_BOSS_Major_SphereNormal1_SetSphere.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Boss/Spr_BOSS_Major_SphereNormal1_AttackReady.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Boss/Spr_BOSS_Major_SphereNormal1_Attack.csv"));

	// Move 
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Boss/Spr_BOSS_Major_Normal1_TeleportStart.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Boss/Spr_BOSS_Major_MoveEnd.csv"));

	// Rush Attack
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Boss/Spr_BOSS_Major_RushReady.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Boss/Spr_BOSS_Major_RushEndTeleport.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Boss/Spr_BOSS_Major_RushEnd.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Boss/Spr_BOSS_Major_RushAttack.csv"));

	// Normal1_Attack
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Boss/Spr_BOSS_Major_Normal1_Attack.csv"));

	MajorPos.push_back({ 7380.f , 1710.f}); // LEFT DOWN
	MajorPos.push_back({ 7585.f , 1310.f}); // LEFT TOP
	MajorPos.push_back({ 8035.f , 1610.f}); // MID
	MajorPos.push_back({ 8495.f , 1310.f}); // RIGHT DOWN
	MajorPos.push_back({ 8710.f , 1710.f}); // RIGHT TOP

	SetPosition(MajorPos[static_cast<int>(MajorPosition::MID)]);
	currentPosition = MajorPosition::MID;

	SetAnimationEvent();
}

void BossMajor::Reset()
{
	Enemy::Reset();
}

void BossMajor::Update(float dt)
{
	Enemy::Update(dt);
	frail->Update(dt);

	if (!animator->IsPlaying())
	{
		animator->Play("Spr_BOSS_Major_Idle");
		currentStauts = Status::IDLE;
	}

	switch (currentStauts)
	{
		case BossMajor::Status::NONE:
			break;
		case BossMajor::Status::IDLE:
			if (GetPosition().x < player->GetPosition().x)
			{
				SetFlipX(false);
			}
			else
			{
				SetFlipX(true);
			}

			if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
			{
				currentStauts = Status::SPHERE_ATTACK;
			}
			else if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
			{
				currentStauts = Status::MOVE;
			}
			else if (InputMgr::GetKeyDown(sf::Keyboard::Num4))
			{
				currentStauts = Status::RUSH_ATTACK;
			}

			else if (InputMgr::GetKeyDown(sf::Keyboard::Num5))
			{
				currentStauts = Status::NORMAL1_ATTACK;
			}
			break;
		case BossMajor::Status::SPHERE_ATTACK:
			if (!isSphere_Attack)
			{
				isSphere_Attack = true;
				animator->Play("Spr_BOSS_Major_SphereNormal1_SetSphere");
			}
			break;

		case BossMajor::Status::MOVE:
			if (!isMove)
			{
				isMove = true;
				animator->Play("Spr_BOSS_Major_Normal1_TeleportStart");
			}
			break;

		case BossMajor::Status::RUSH_ATTACK:
			if (!isRush_Attack)
			{
				isRush_Attack = true;
				animator->Play("Spr_BOSS_Major_RushReady");
			}
			break;

		case BossMajor::Status::NORMAL1_ATTACK:
			if (!isNormal1_Attack)
			{
				isNormal1_Attack = true;
				animator->Play("Spr_BOSS_Major_Normal1_TeleportStart");
			}
			break;
		default:

			break;
	}
}

void BossMajor::LateUpdate(float dt)
{
	Enemy::LateUpdate(dt);

	frail->LateUpdate(dt);
}

void BossMajor::Dead()
{

}

void BossMajor::Draw(sf::RenderWindow& window)
{
	Enemy::Draw(window);

	frail->Draw(window);
}

void BossMajor::SetAnimationEvent()
{
	// ***********************SPHERE_ATTACK Event***********************
	animator->AddEvent("Spr_BOSS_Major_SphereNormal1_SetSphere", 12, [this]()
		{
			SetTexture("graphics/Enemy/Boss_Major/P1/Spr_BOSS_Major_SphereNormal1_AttackReady/Spr_BOSS_Major_SphereNormal1_AttackReady (3).png");
			SetOrigin(Origins::BC);
			animator->Play("Spr_BOSS_Major_SphereNormal1_AttackReady");
		});

	animator->AddEvent("Spr_BOSS_Major_SphereNormal1_AttackReady", 25, [this]()
		{
			SetTexture("graphics/Enemy/Boss_Major/P1/Spr_BOSS_Major_SphereNormal1_Attack/Spr_BOSS_Major_SphereNormal1_Attack (1).png");
			SetOrigin(Origins::BC);
			animator->Play("Spr_BOSS_Major_SphereNormal1_Attack");
		});

	// **********************SphereNormal End Event**********************
	animator->AddEvent("Spr_BOSS_Major_SphereNormal1_Attack", 4, [this]()
		{
			SetTexture("graphics/Enemy/Boss_Major/Spr_BOSS_Major_Idle.png");
			SetOrigin(Origins::BC);

			frail->SetPosition(GetPosition());
			frialAnimator->Play("Spr_Frail_SpinLoop");
			isSphere_Attack = false;
			currentStauts = Status::IDLE;
		});

	// **************************Move Event**************************
	animator->AddEvent("Spr_BOSS_Major_Normal1_TeleportStart", 7, [this]()
		{
			switch (currentStauts)
			{
				case BossMajor::Status::MOVE:
					{
						MajorPosition random = static_cast<MajorPosition>(Utils::RandomRange(0, 5));
						while (currentPosition == random)
						{

							random = static_cast<MajorPosition>(Utils::RandomRange(0, 5));
						}
						currentPosition = random;
						animator->Play("Spr_BOSS_Major_MoveEnd");
						SetPosition(MajorPos[static_cast<int>(currentPosition)]);
						isMove = false;
						break;
					}
	
				case BossMajor::Status::NORMAL1_ATTACK:
					SetPosition({ player->GetPosition().x - 110 , player->GetPosition().y - 80 });
					animator->Play("Spr_BOSS_Major_Normal1_Attack");
					isMove = false;
					break;
			}

		});

	animator->AddEvent("Spr_BOSS_Major_RushReady", 9, [this]()
		{
			SetTexture("graphics/Enemy/Boss_Major/P1/Spr_BOSS_Major_RushReady/Spr_BOSS_Major_RushReady (10).png");
			SetOrigin(Origins::BC);

		});

	animator->AddEvent("Spr_BOSS_Major_RushReady", 13, [this]()
		{
			SetTexture("graphics/Enemy/Boss_Major/P1/Spr_BOSS_Major_RushReady/Spr_BOSS_Major_RushReady (15).png");
			SetOrigin(Origins::BC);
		});

	animator->AddEvent("Spr_BOSS_Major_RushReady", 24, [this]()
		{
			SetTexture("graphics/Enemy/Boss_Major/Spr_BOSS_Major_Idle.png");
			SetOrigin(Origins::BC);

			animator->Play("Spr_BOSS_Major_RushEndTeleport");
		});

	animator->AddEvent("Spr_BOSS_Major_RushEndTeleport", 3, [this]()
		{
			SetPosition({ player->GetPosition().x ,  player->GetPosition().y - 100});
			animator->Play("Spr_BOSS_Major_RushEnd");
		});

	animator->AddEvent("Spr_BOSS_Major_RushEnd", 7, [this]()
		{
			animator->Play("Spr_BOSS_Major_RushAttack");
		});

	animator->AddEvent("Spr_BOSS_Major_RushAttack", 4, [this]()
		{
			currentStauts = Status::MOVE;
			isRush_Attack = false;
			isMove = false;
		});

	// NormalAttack 1
	animator->AddEvent("Spr_BOSS_Major_Normal1_Attack", 7, [this]()
		{
			currentStauts = Status::MOVE;
			isNormal1_Attack = false;
			isMove = false;
		});

}

void BossMajor::RandomMove()
{
}
