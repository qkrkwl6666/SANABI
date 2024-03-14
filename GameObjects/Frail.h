#pragma once
#include "SpriteGo.h"

class Player;
class BossMajor;

class Frail : public SpriteGo
{
	enum class Status
	{
		NONE,
		IDLE,
		MOVE,
		COUNT,
	};

protected:
	Animator* animator = nullptr;
	Player* player = nullptr;
	BossMajor* bossMajor = nullptr;
	float moveSpeed = 300.f;

	sf::Vector2f direction;

	// ���� �÷��̾� �Ѿư��� �ð�
	float moveDt = 0.f;
	float moveTime = 10.f;

	// ���� ���� ��ȯ 
	float moveIdleDt = 30.f;
	float moveDuration = 30.f;

	Status currentStatus = Status::IDLE;

public:
	Frail(const std::string& name , BossMajor* bossMajor);
	~Frail() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	Animator* GetAnimator();
};

