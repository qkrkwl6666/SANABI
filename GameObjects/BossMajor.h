#pragma once
#include "Enemy.h"

class Frail;
class Player;
class Grenade;

class BossMajor : public Enemy
{
public:
	enum class Status
	{
		NONE,
		IDLE,
		MOVE,
		SPHERE_ATTACK,
		RUSH_ATTACK,
		NORMAL1_ATTACK,
		GRENADES_ATTACK,
		TAKE_DOWN,
		DAMAGED_KNOCK_BACK,
		CHANGE_PAGE,
		COUNT,
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
protected:
	std::vector<sf::Vector2f> MajorPos;

	Player* player = nullptr;
	Frail* frail = nullptr;
	Animator* frialAnimator = nullptr;
	Grenade* greande = nullptr;
	Status currentStauts = Status::IDLE;
	
	MajorPosition currentPosition;

	float idleDt = 0.f;
	float idleDuration = 2.f;

	float rushSpeed = 300.f;
	float KnockBackSpeed = 50.f;

	int hp = 10;

	bool isChangePage = false;
	bool isFight = false;
	bool isSphere_Attack = false;
	bool isMove = false;
	bool isRush_Attack = false;
	bool isRush_Attacking = false;
	bool isNormal1_Attack = false;
	bool isNormal1_Attacking = false;
	bool isGrenades_Attack = false;
	bool isTakeDown = false;
	bool isDamagedKnockBack = false;

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
	void isMoving();

	void SetCurrentStatus(Status status);
	void SetFight(bool isFight = true){ this->isFight = isFight; }

	void SkillCencle();

	void Flip();
};

