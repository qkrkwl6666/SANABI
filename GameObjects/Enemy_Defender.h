#pragma once
#include "Enemy.h"
class Enemy_Defender : public Enemy
{
protected:
	enum class Status
	{
		NONE,
		IDLE,
		DEAD,
		ATTACK,
		ATTACK_COOLTIME,
		STURNED,
		ATTACKED,

	};

public:
	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

