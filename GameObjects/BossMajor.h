#pragma once
#include "Enemy.h"

class Frail;
class Player;

class BossMajor : public Enemy
{
protected:
	enum class Status
	{
		NONE,
		IDLE,
		SPHERE_ATTACK,
		MOVE,
		RUSH_ATTACK,
		NORMAL1_ATTACK,


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

	Player* player = nullptr;
	Frail* frail = nullptr;
	Animator* frialAnimator = nullptr;

	Status currentStauts = Status::NONE;
	
	MajorPosition currentPosition;

	bool isSphere_Attack = false;
	bool isMove = false;
	bool isRush_Attack = false;
	bool isNormal1_Attack = false;

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
	void RandomMove();
};

