#include "pch.h"
#include "Player.h"

Player::Player(const std::string& name) : SpriteGo(name)
{

}

Player::~Player()
{

}

void Player::Init()
{
	SpriteGo::Init();

	animator.SetTarget(&sprite);
}

void Player::Reset()
{
	SpriteGo::Reset();
	animator.ClearEvent();
	
	animator.Play("Data/Player_Idle.csv");
	SetOrigin(Origins::MC);
	SetPosition({ FRAMEWORK.GetWindowSize().x * 0.5f ,
		FRAMEWORK.GetWindowSize().y * 0.5f });
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);
}


