#include "pch.h"
#include "Bullet.h"
#include "SceneGame.h"
#include "Enemy_RifleMan.h"
#include "Player.h"

Bullet::Bullet(const std::string& name)
{
	player = dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetPlayer();

	SetTexture("graphics/Enemy/RifleMan/Spr_Bullet_Rifleman.png");

	SetScale({ 2.f , 2.f });
	SetOrigin(Origins::MC);

	SetActive(false);
}

Bullet::~Bullet()
{

}

void Bullet::Init()
{
	SpriteGo::Init();

}

void Bullet::Reset()
{
	SpriteGo::Reset();
}

void Bullet::Update(float dt)
{
	SpriteGo::Update(dt);
	activeDt += dt;

	Translate(dirction * dt * speed);

	if (GetGlobalBounds().intersects(player->GetGlobalBounds()))
	{
		SetActive(false);
		// TODO : 데미지 처리
	}

	if (activeDt >= activeDuration)
	{
		SetActive(false);
		activeDt = 0.f;
	}

}

void Bullet::LateUpdate(float dt)
{
	SpriteGo::LateUpdate(dt);
}

void Bullet::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Bullet::Shooting(const sf::Vector2f& dir , Enemy_RifleMan* rifleMan)
{
	this->rifleMan = rifleMan;
	dirction = dir;
	activeDt = 0.f;
	SetPosition(rifleMan->GetPosition());
	SetRotation(Utils::Angle(dir) + 90.f);
	SetActive(true);
}
