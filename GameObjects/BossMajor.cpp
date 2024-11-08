#include "pch.h"
#include "BossMajor.h"
#include "Frail.h"
#include "Player.h"
#include "SceneGame.h"
#include "Grenade.h"
#include "BossMajor.h"

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
	greande = new Grenade("Grenade", this);

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

	// GRenades_Attack
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Boss/Spr_BOSS_Major_Melee1_Attack.csv"));

	// TakeDown
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/TakeDown/Major_TakeDown.csv"));

	// DamagedKnockback
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Boss/Spr_BOSS_Major_DamagedKnockback.csv"));

	// ChangePage
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Boss/Spr_BOSS_Major_ChangePage.csv"));

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
	
	if (frail->GetActive())
	{
		frail->Update(dt);
	}

	greande->Update(dt);

	if (!animator->IsPlaying())
	{
		animator->Play("Spr_BOSS_Major_Idle");
		currentStauts = Status::IDLE;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		currentStauts = Status::SPHERE_ATTACK;
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
	{
		currentStauts = Status::CHANGE_PAGE;
	}

	switch (currentStauts)
	{
		case BossMajor::Status::NONE:
			break;
		case BossMajor::Status::IDLE:
			Flip();

			if (isFight)
			{
				idleDt += dt;
				if (idleDt >= idleDuration)
				{
					currentStauts = static_cast<Status>(Utils::RandomRange(4, 7));
					idleDt = 0.f;
				}
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
			else if (isRush_Attacking)
			{
				sf::Vector2f direction = { 0, 1 };

				Translate(direction * rushSpeed * dt);

				if (Utils::Distance(GetPosition(), player->GetPosition()) < 150 && !player->GetIsInvincible())
				{
					player->Attacked();
				}
			}
			break;

		case BossMajor::Status::NORMAL1_ATTACK:
			if (!isNormal1_Attack)
			{
				isNormal1_Attack = true;
				animator->Play("Spr_BOSS_Major_Normal1_TeleportStart");
			}

			if (isNormal1_Attacking)
			{
				if (Utils::Distance(GetPosition(), player->GetPosition()) < 300 && !player->GetIsInvincible())
				{
					player->Attacked();
				}
			}
			break;

		case BossMajor::Status::GRENADES_ATTACK:
			if (!isGrenades_Attack)
			{
				isGrenades_Attack = true;
				animator->Play("Spr_BOSS_Major_Melee1_Attack");
				greande->GrenadeAttack();
			}
			break;

		case BossMajor::Status::TAKE_DOWN:
			if (!isTakeDown)
			{
				isTakeDown = true;
				animator->Play("Spr_BOSS_Major_TakeDown");
			}
			break;
		case BossMajor::Status::DAMAGED_KNOCK_BACK:
			if (!isDamagedKnockBack)
			{
				SetTexture("graphics/Enemy/Boss_Major/Spr_BOSS_Major_Idle.png");
				SetOrigin(Origins::BC);

				isDamagedKnockBack = true;
				hp--;
				SkillCencle();
				if (hp <= 0)
				{
					currentStauts = Status::CHANGE_PAGE;
					frail->SetActive(false);
					isDamagedKnockBack = false;
					break;
				}
				animator->Play("Spr_BOSS_Major_DamagedKnockback");
			}
			else if (isDamagedKnockBack)
			{
				sf::Vector2f dir = { 1 , 0 };
				if (!GetFlipX())
				{
					dir.x *= -1;
				}

				Translate(dir * dt * KnockBackSpeed);

			}
			break;
		//Spr_BOSS_Major_ChangePage

		case BossMajor::Status::CHANGE_PAGE:
			if (!isChangePage)
			{
				isChangePage = true;
				animator->Play("Spr_BOSS_Major_ChangePage");
			}
			break;

		default:

			break;
	}
}

void BossMajor::LateUpdate(float dt)
{
	Enemy::LateUpdate(dt);

	greande->LateUpdate(dt);
	frail->LateUpdate(dt);
}

void BossMajor::Dead()
{

}

void BossMajor::Draw(sf::RenderWindow& window)
{
	greande->Draw(window);

	if (frail->GetActive())
	{
		frail->Draw(window);
	}

	Enemy::Draw(window);
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
			frail->SetActive(true);
			frialAnimator->Play("Spr_Frail_SpinLoop");
			isSphere_Attack = false;
			currentStauts = Status::IDLE;
		});

	// **************************Move Event**************************
	animator->AddEvent("Spr_BOSS_Major_Normal1_TeleportStart", 7, [this]()
		{
			RandomMove();
		});

	animator->AddEvent("Spr_BOSS_Major_MoveEnd", 9, [this]()
		{
			currentStauts = Status::IDLE;
			isMove = false;
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

			animator->Play("Spr_BOSS_Major_RushEnd");
		});

	animator->AddEvent("Spr_BOSS_Major_RushEndTeleport", 3, [this]()
		{
			currentStauts = Status::MOVE;
			RandomMove();

			isRush_Attack = false;
			isMove = true;
		});

	animator->AddEvent("Spr_BOSS_Major_RushEnd", 7, [this]()
		{
			animator->Play("Spr_BOSS_Major_RushAttack");
			SetPosition({ player->GetPosition().x ,  player->GetPosition().y - 200 });
			isRush_Attacking = true;
		});

	animator->AddEvent("Spr_BOSS_Major_RushAttack", 4, [this]()
		{
			animator->Play("Spr_BOSS_Major_RushEndTeleport");
			isRush_Attacking = false;
		});

	// NormalAttack 1
	animator->AddEvent("Spr_BOSS_Major_Normal1_Attack", 8, [this]()
		{
			MajorPosition random = static_cast<MajorPosition>(Utils::RandomRange(0, 5));
			while (currentPosition == random)
			{
				random = static_cast<MajorPosition>(Utils::RandomRange(0, 5));
			}
			currentPosition = random;
			SetPosition(MajorPos[static_cast<int>(currentPosition)]);
			isNormal1_Attack = false;
			currentStauts = Status::IDLE;
			isNormal1_Attacking = false;
		});

	// GRENADES_ATTACK

	animator->AddEvent("Spr_BOSS_Major_Melee1_Attack", 6, [this]()
		{
			currentStauts = Status::MOVE;
			isMove = true;
			RandomMove();
			isGrenades_Attack = false;
		});

	// TAKE_DOWN
	animator->AddEvent("Spr_BOSS_Major_TakeDown", 15, [this]()
		{
			isMoving();
			isTakeDown = false;
		});

	//DAMAGED_KNOCK_BACK
	animator->AddEvent("Spr_BOSS_Major_DamagedKnockback", 15, [this]()
		{
			currentStauts = Status::MOVE;
			isMove = true;
			RandomMove();
			isDamagedKnockBack = false;
		});

	//CHANGE_PAGE
	animator->AddEvent("Spr_BOSS_Major_ChangePage", 67, [this]()
		{
			SkillCencle();
			SCENE_MGR.ChangeScene(SceneIds::SceneTitle);
		});
}

void BossMajor::RandomMove()
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
			break;
		}

		case BossMajor::Status::NORMAL1_ATTACK:

			if (GetFlipX())
			{
				SetPosition({ player->GetPosition().x + 110 , player->GetPosition().y - 80 });
			}
			else
			{
				SetPosition({ player->GetPosition().x - 110 , player->GetPosition().y - 80 });
			}
			animator->Play("Spr_BOSS_Major_Normal1_Attack");
			isNormal1_Attacking = true;
			//isMove = false;
			break;
	}
}

void BossMajor::isMoving()
{
	MajorPosition random = static_cast<MajorPosition>(Utils::RandomRange(0, 5));
	while (currentPosition == random)
	{
		random = static_cast<MajorPosition>(Utils::RandomRange(0, 5));
	}
	currentPosition = random;
	SetPosition(MajorPos[static_cast<int>(currentPosition)]);

	currentStauts = Status::IDLE;
}

void BossMajor::SetCurrentStatus(Status status)
{
	currentStauts = status;
}

void BossMajor::SkillCencle()
{
	isSphere_Attack = false;
	isMove = false;
	isRush_Attack = false;
	isRush_Attacking = false;
	isNormal1_Attack = false;
	isNormal1_Attacking = false;
	isGrenades_Attack = false;
	isTakeDown = false;
}

void BossMajor::Flip()
{
	if (GetPosition().x < player->GetPosition().x)
	{
		SetFlipX(false);
	}
	else
	{
		SetFlipX(true);
	}
}
