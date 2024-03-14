#include "pch.h"
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

	SetTexture("graphics/Enemy/Boss_Major/Spr_BOSS_Major_Idle.png");
	SetScale({ 2.f , 2.f });
	SetOrigin(Origins::BC);

	animator->SetTarget(&sprite);
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Boss/Spr_BOSS_Major_Idle.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Boss/Spr_BOSS_Major_SphereNormal1_SetSphere.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Boss/Spr_BOSS_Major_SphereNormal1_AttackReady.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Boss/Spr_BOSS_Major_SphereNormal1_Attack.csv"));

	MajorPos.push_back({ 7380.f , 1710.f}); // LEFT DOWN
	MajorPos.push_back({ 7585.f , 1310.f}); // LEFT TOP
	MajorPos.push_back({ 8035.f , 1610.f}); // MID
	MajorPos.push_back({ 8495.f , 1310.f}); // RIGHT DOWN
	MajorPos.push_back({ 8710.f , 1710.f}); // RIGHT TOP

	SetPosition(MajorPos[static_cast<int>(MajorPosition::MID)]);

	SetAnimationEvent();
}

void BossMajor::Reset()
{
	Enemy::Reset();
}

void BossMajor::Update(float dt)
{
	Enemy::Update(dt);

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
			if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
			{
				currentStauts = Status::SPHERE_ATTACK;
			}
			break;
		case BossMajor::Status::SPHERE_ATTACK:
			if (!isSphere_Attack)
			{
				isSphere_Attack = true;
				animator->Play("Spr_BOSS_Major_SphereNormal1_SetSphere");
			}
			break;
		default:

			break;
	}
}

void BossMajor::LateUpdate(float dt)
{
	Enemy::LateUpdate(dt);
}

void BossMajor::Dead()
{

}

void BossMajor::Draw(sf::RenderWindow& window)
{
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

	// **********************SphereNormal 끝 이벤트**********************
	animator->AddEvent("Spr_BOSS_Major_SphereNormal1_Attack", 4, [this]()
		{
			SetTexture("graphics/Enemy/Boss_Major/Spr_BOSS_Major_Idle.png");
			SetOrigin(Origins::BC);
			isSphere_Attack = false;
			currentStauts = Status::IDLE;
		});
}
