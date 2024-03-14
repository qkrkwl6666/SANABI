#pragma once
#include "SpriteGo.h"

class Enemy_RifleMan;
class Player;

class Bullet : public SpriteGo
{
protected:
	sf::Vector2f dirction;

	Enemy_RifleMan* rifleMan = nullptr;
	Player* player = nullptr;

	float speed = 200.f;
	float damage;

	float activeDt = 0.f;
	float activeDuration = 5.f;

public:
	Bullet(const std::string& name = "");
	~Bullet() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Shooting(const sf::Vector2f& dir , 
		Enemy_RifleMan* rifleMan);
};

