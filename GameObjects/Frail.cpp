#include "pch.h"
#include "Frail.h"
#include "SceneGame.h"
#include "Player.h"

Frail::Frail(const std::string& name, BossMajor* bossMajor) 
	: SpriteGo(name) , bossMajor(bossMajor)
{
	Init();
}

Frail::~Frail()
{
	if (animator != nullptr)
	{
		delete animator;
		animator = nullptr;
	}
}

void Frail::Init()
{
	SpriteGo::Init();

	SetTexture("graphics/Enemy/Boss_Major/Frail/Spr_Frail_SpinLoop (lp) (1).png");
	SetScale({ 2.f , 2.f });
	SetOrigin(Origins::MC);
	animator = new Animator();
	animator->SetTarget(&sprite);

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Boss/Spr_Frail_SpinLoop.csv"));

	player = dynamic_cast<SceneGame*>
		(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetPlayer();

	SetActive(false);
}

void Frail::Reset()
{
	SpriteGo::Reset();
}

void Frail::Update(float dt)
{
	SpriteGo::Update(dt);

	animator->Update(dt);
	
	switch (currentStatus)
	{
		case Frail::Status::NONE:

			break;
		case Frail::Status::IDLE:
			moveIdleDt += dt;

			if (moveIdleDt >= moveDuration)
			{
				currentStatus = Status::MOVE;
				moveIdleDt = 0.f;
			}
			break;
		case Frail::Status::MOVE:
			moveDt += dt;

			direction = player->GetPosition() - GetPosition();
			Utils::Normalize(direction);

			Translate(direction * dt * moveSpeed);

			if (moveDt >= moveTime)
			{
				currentStatus = Status::IDLE;
				moveDt = 0.f;
			}
			break;
		case Frail::Status::COUNT:

			break;
		default:
			break;
	}
	
}

void Frail::LateUpdate(float dt)
{
	SpriteGo::LateUpdate(dt);

	if (GetGlobalBounds().intersects(player->GetGlobalBounds()) && !player->GetIsInvincible())
	{
		player->Attacked();
	}
}

void Frail::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

Animator* Frail::GetAnimator()
{
	if (animator != nullptr)
	{
		return animator;
	}

	std::cout << "Frail animator nulltpr !!" << std::endl;
}
