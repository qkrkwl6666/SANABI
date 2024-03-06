#include "pch.h"
#include "Weapon.h"
#include "SceneTitle.h"
#include "Player.h";
#include "Animator.h"

Weapon::Weapon(const std::string& name) : SpriteGo(name)
{
	
}

Weapon::~Weapon()
{
	if (animator != nullptr)
	{
		delete animator;
		animator = nullptr;
	}
}

void Weapon::Init()
{
	SpriteGo::Init();

	animator = new Animator();

	animator->SetTarget(&sprite);
	player = dynamic_cast<SceneTitle*>
		(SCENE_MGR.GetScene(SceneIds::SceneTitle))->GetPlayer();

	SetScale({ 2.5f , 2.5f });
	SetOrigin(Origins::MC);;

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Arm_Idle.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Arm_Running.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Arm_Jumping.csv"));
}

void Weapon::Reset()
{
	SpriteGo::Reset();

	animator->ClearEvent();
                                 
	//animator->Play("data/Animations/Player_Arm_Idle.csv");
	 
	animator->Play("Player_Arm_Idle");
}

void Weapon::Update(float dt)
{
	SpriteGo::Update(dt);

	animator->Update(dt);
}

Animator* Weapon::GetAnimator()
{
	if (animator != nullptr)
	{
		return animator;
	}
	
	std::cout << "weapon animator nulltpr !!" << std::endl;
}

