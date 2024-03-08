#include "pch.h"
#include "Player.h"
#include "Animator.h"
#include "AniTest2.h"
#include "Weapon.h"

Player::Player(const std::string& name)
	:SpriteGo(name)
{

}

Player::~Player()
{
	Delete();
}

//void Player::TestStatic()
//{
//	std::cout << "TestStatic" << std::endl;
//}
//
//void Player::TestInstance()
//{
//	std::cout << "TestInstance" << std::endl;
//}

void Player::Init()
{
	// TODO : 플레이어 sortLayer 하면 팅기는 현상있음 
	SpriteGo::Init();
	animator = new Animator();
	animator->SetTarget(&sprite);

	weapon = new Weapon("Weapon");
	SCENE_MGR.GetScene(SceneIds::SceneTitle)->AddGo(weapon);
	// weapon->Init();
	// weapon->Reset();
	SetScale({ 3.f , 3.f });

	SetOrigin(Origins::MC);

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Idle.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Running.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Jumping.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Run_Landing.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Fall_Start.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Falling.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Run_Stop.csv"));

	/*auto* clip = animator->GetClip("Player_Run_Landing");
	clip->fps = 30;*/
	
	//animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Run.csv"));
}

void Player::Reset()
{
	animator->ClearEvent();

	//std::function<void()> funcInstance = std::bind(&Player::PlayerFalling, this);
	//std::function<void()> funcInstance2 = std::bind(&Player::PlayerJumping, this);
	//animator->AddEvent("Player_Fall_Start", 2, funcInstance);
	//animator->AddEvent("Player_Falling", 2, funcInstance2);

	//std::function<void()> funcStatic = std::bind(&Player::TestStatic);
	//animator.AddEvent("data/Idle.csv", 5, funcStatic);

	/*PlayerAnimationPlay("data/Animations/Player_Idle.csv",
		"data/Animations/Player_Arm_Idle.csv");*/
	weaponAnimator = weapon->GetAnimator();

	animator->Play("Player_Idle");
	weaponAnimator->Play("Player_Arm_Idle");

	WeaponPoint = { GetPosition().x - 30, GetPosition().y + 30 };

	weapon->SetPosition(WeaponPoint);

	SetOrigin(Origins::MC);
	SetPosition({ FRAMEWORK.GetWindowSize().x * 0.5f ,
		FRAMEWORK.GetWindowSize().y * 0.5f });
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);
	animator->Update(dt);

	float h = InputMgr::GetAxisRaw(Axis::Horizontal); // - 1 0 1

	if (isGround && InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		isGround = false;
		animator->Play("Player_Jumping");
		weaponAnimator->Play("Player_Arm_Jumping");
		velocity.y = -500.f;
	}

	velocity.x = h * speed;
	velocity.y += gravity * dt;
	position += velocity * dt;

	if (velocity.y > 100.f && !isGround && !Falling)
	{
		animator->Play("Player_Falling");
		weaponAnimator->Play("Player_Arm_Falling");
		Falling = true;
	}

	if (position.y > FRAMEWORK.GetWindowSize().y * 0.5f)
	{
		isGround = true;
		position.y = FRAMEWORK.GetWindowSize().y * 0.5f;
		velocity.y = 0.f;
	}

	SetPosition(position);

	if (!animator->IsPlaying())
	{
		animator->Play("Player_Idle");
		weaponAnimator->Play("Player_Arm_Idle");
	}

	if (h != 0.f)
	{
		SetFlipX(h < 0);
		weapon->SetFlipX(h < 0);
	}

	if (!weapon->GetFlipX())
	{
		WeaponPoint = { -30.f , -30.f };
	}
	else
	{
		WeaponPoint = { 30.f , - 30.f};
	}

	if (animator->GetCurrentClipId() == "Player_Idle")
	{
		if (h != 0.f)
		{
			animator->Play("Player_Running");
			weaponAnimator->Play("Player_Arm_Running");
		}
	}
	else if (animator->GetCurrentClipId() == "Player_Running")
	{
		if (h == 0.f)
		{
			animator->Play("Player_Run_Stop");
			weaponAnimator->Play("Player_Arm_Run_Stop");
		}
	}

	else if ((animator->GetCurrentClipId() == "Player_Jumping" || 
		animator->GetCurrentClipId() == "Player_Falling") && isGround)
	{
		if (h == 0.f)
		{
			animator->Play("Player_Idle");
			weaponAnimator->Play("Player_Arm_Idle");
		}
		else
		{
			animator->Play("Player_Running");
			weaponAnimator->Play("Player_Arm_Running");
		}
		Falling = false;
	}

	weapon->SetPosition(GetPosition() + WeaponPoint);
}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	weapon->Draw(window);
}

void Player::PlayerAnimationPlay(const std::string& player, const std::string& weapon, bool clearQueue)
{
	animator->Play(player , clearQueue);
	weaponAnimator->Play(weapon , clearQueue);
}

void Player::PlayerFalling()
{
	std::cout << "Player_Falling!!" << std::endl;
	animator->Play("Player_Falling");
}

void Player::PlayerJumping()
{
	std::cout << "Player_Jumping!!" << std::endl;
	animator->Play("Player_Jumping");
}

void Player::Delete()
{
	if (animator != nullptr)
	{
		delete animator;
		animator = nullptr;
	}
}
