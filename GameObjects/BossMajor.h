#pragma once
#include "Enemy.h"


class BossMajor : public Enemy
{
protected:
	enum class Status
	{
		NONE,
		IDLE,
		SPHERE_ATTACK,

	};

	enum class MajorPosition
	{
		LEFT_DOWN,
		LEFT_TOP,
		MID,
		RIGHT_DOWN,
		RIGHT_TOP,
		COUNT,
	};

	std::vector<sf::Vector2f> MajorPos;

	Status currentStauts = Status::NONE;

	bool isSphere_Attack = false;

public:
	BossMajor(const std::string& name = "");
	~BossMajor() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Dead() override;
	void Draw(sf::RenderWindow& window) override;

	void SetAnimationEvent();
};

