#include "pch.h"
#include "Grenade.h"
#include "SpriteAnimatorGo.h"
#include "SceneGame.h"
#include "BossMajor.h"
#include "Player.h"

Grenade::Grenade(const std::string& name, BossMajor* bossMajor) 
	: SpriteGo(name) , bossMajor(bossMajor)
{
	Init();
}

Grenade::~Grenade()
{
	for (auto* data : grenades)
	{
		if (data != nullptr)
		{
			delete data;
		}
	}
}

void Grenade::Init()
{
	//grenades.resize(3 , new SpriteAnimatorGo());

	grenades.push_back(new SpriteAnimatorGo());
	grenades.push_back(new SpriteAnimatorGo());
	grenades.push_back(new SpriteAnimatorGo());

	player = dynamic_cast<SceneGame*>
		(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetPlayer();

	for (auto& data : grenades)
	{
		data->SetTexture("graphics/Enemy/Boss_Major/P1/Spr_BOSS_Grenade/Spr_BOSS_Grenade_Idle (lp) (6).png");
		data->SetOrigin(Origins::MC);
		data->SetScale({ 2.f , 2.f });
		data->GetAnimator()->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Boss/Spr_BOSS_Grenade_Idle.csv"));
		data->GetAnimator()->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Boss/Spr_BOSS_Grenade_Explode.csv"));

		SetActive(false);
	}

	grenades[0]->GetAnimator()->AddEvent("Spr_BOSS_Grenade_Idle", 5, [this]() 
		{ 
			grenades[0]->SetTexture("graphics/Enemy/Boss_Major/P1/Spr_BOSS_Grenade/Spr_BOSS_Grenade_Explode (5).png");
			grenades[0]->SetOrigin(Origins::MC);
			grenades[0]->GetAnimator()->Play("Spr_BOSS_Grenade_Explode");
		});

	grenades[1]->GetAnimator()->AddEvent("Spr_BOSS_Grenade_Idle", 5, [this]()
		{
			grenades[1]->SetTexture("graphics/Enemy/Boss_Major/P1/Spr_BOSS_Grenade/Spr_BOSS_Grenade_Explode (5).png");
			grenades[1]->SetOrigin(Origins::MC);
			grenades[1]->GetAnimator()->Play("Spr_BOSS_Grenade_Explode");
		});

	grenades[2]->GetAnimator()->AddEvent("Spr_BOSS_Grenade_Idle", 5, [this]()
		{
			grenades[2]->SetTexture("graphics/Enemy/Boss_Major/P1/Spr_BOSS_Grenade/Spr_BOSS_Grenade_Explode (5).png");
			grenades[2]->SetOrigin(Origins::MC);
			grenades[2]->GetAnimator()->Play("Spr_BOSS_Grenade_Explode");
		});

	SpriteGo::Init();
}

void Grenade::Reset()
{
	SpriteGo::Reset();
}

void Grenade::Update(float dt)
{
	SpriteGo::Update(dt);

	for (auto& data : grenades)
	{
		if (!data->GetAnimator()->IsPlaying())
		{
			data->SetActive(false);
		}
		if (!data->GetActive())
		{
			return;
		}
		gravityTime += dt;
		if (gravityTime >= gravityDt)
		{
			gravity.y += 0.01;
			gravityDt = 0.f;
		}
		data->Translate(gravity * dt * speed);
		
		data->Update(dt);

		if (data->GetAnimator()->GetCurrentClipId() == "Spr_BOSS_Grenade_Explode")
		{
			if (data->GetGlobalBounds().intersects(player->GetGlobalBounds()) && !player->GetIsInvincible())
			{
				player->Attacked();
			}
		}

	}
}

void Grenade::LateUpdate(float dt)
{
	SpriteGo::LateUpdate(dt);

	for (auto& data : grenades)
	{
		data->LateUpdate(dt);
	}
}

void Grenade::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);

	for (auto& data : grenades)
	{
		if (!data->GetActive())
		{
			return;
		}
		data->Draw(window);
	}
}

void Grenade::GrenadeAttack()
{
	int x = 30;
	int y = 30;
	for (auto& data : grenades)
	{
		data->SetTexture("graphics/Enemy/Boss_Major/P1/Spr_BOSS_Grenade/Spr_BOSS_Grenade_Idle (lp) (6).png");
		data->SetOrigin(Origins::MC);

		data->SetActive(true);
		if (!bossMajor->GetFlipX())
		{
			data->SetPosition({ bossMajor->GetPosition().x + x,
			bossMajor->GetPosition().y + y });
			data->GetAnimator()->Play("Spr_BOSS_Grenade_Idle");
			gravity = { 0 , -1 };
			x += 250;
			y -= 100;
		}
		else
		{
			data->SetPosition({ bossMajor->GetPosition().x + x,
			bossMajor->GetPosition().y + y });
			data->GetAnimator()->Play("Spr_BOSS_Grenade_Idle");
			gravity = { 0 , -1 };
			x -= 250;
			y -= 100;
		}


	}
}

