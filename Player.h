#pragma once
#include "SpriteGo.h"

class Player : public SpriteGo
{
protected:
	Animator animator;

	sf::Vector2f direction;
	float speed = 500.f;
public:
	Player(const std::string& name = "");
	~Player();

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	//void Draw(float dt) override;

	
};

