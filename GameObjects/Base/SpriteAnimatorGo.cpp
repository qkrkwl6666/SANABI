#include "pch.h"
#include "SpriteAnimatorGo.h"

SpriteAnimatorGo::SpriteAnimatorGo(const std::string& name)
	: SpriteGo(name)
{
	Init();
}

SpriteAnimatorGo::~SpriteAnimatorGo()
{

}

void SpriteAnimatorGo::Init()
{
	SpriteGo::Init();
	
	animator = std::make_shared<Animator>();
	animator->SetTarget(&sprite);
}

void SpriteAnimatorGo::Reset()
{
	SpriteGo::Reset();

}

void SpriteAnimatorGo::Update(float dt)
{
	SpriteGo::Update(dt);

	animator->Update(dt);
}

void SpriteAnimatorGo::LateUpdate(float dt)
{
	SpriteGo::LateUpdate(dt);
}

void SpriteAnimatorGo::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);

}
