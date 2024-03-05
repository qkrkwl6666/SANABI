#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class AniTest : public SpriteGo
{
protected:
	Animator animator;

	float gravity = 800.f;
	float speed = 1000.f;
	sf::Vector2f velocity; // 속도 // 방향 * speed
	bool isGround = true;


public:
	AniTest(const std::string& name = "");
	~AniTest() override = default;

	static void TestStatic();
	void TestInstance();

	void Init() override;
	void Reset() override;
	void Update(float dt) override;

};


