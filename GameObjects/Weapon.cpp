#include "pch.h"
#include "Weapon.h"
#include "SceneGame.h"
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
	player = dynamic_cast<SceneGame*>
		(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetPlayer();
	
	SetScale({ 1.5f , 1.5f });
	SetOrigin(Origins::MC);;

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Arm_Idle.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Arm_Running.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Arm_Jumping.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Arm_Falling.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Arm_Run_Stop.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Arm_Ceiling_Stick_Idle.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Arm_Ceiling_Stick_Moving.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Arm_Shift_Rolling.csv"));

	// Shift ChargeDesh
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Charge_Dash/Arm_Charge_Dash_Charge_Start.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Charge_Dash/Arm_Charge_Dash_Charge_Loop.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Charge_Dash/Arm_Charge_Attack.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Charge_Dash/Arm_Charge_Dash_Charge_End.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Charge_Dash/Arm_Charge_Dash_End_Ground.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Charge_Dash/Arm_Charge_Dash.csv"));

}

void Weapon::Reset()
{
	SpriteGo::Reset();

	animator->ClearEvent();
	 
	animator->Play("Player_Arm_Idle");
}

void Weapon::Update(float dt)
{
	SpriteGo::Update(dt);

	animator->Update(dt);

}

void Weapon::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

Animator* Weapon::GetAnimator()
{
	if (animator != nullptr)
	{
		return animator;
	}
	
	std::cout << "weapon animator nulltpr !!" << std::endl;
}

