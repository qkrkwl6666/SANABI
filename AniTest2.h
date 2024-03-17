#pragma once

#include "SpriteGo.h"
#include "Animator.h"

class AniTest2 : public SpriteGo
{
	//애니메이션 조건 검사 구조체
public:
	struct ClipInfo // AnimationClipInfo
	{
		std::string idle;
		std::string move;
		bool flipX = false;
		sf::Vector2f point; // 점 포인트

		ClipInfo()
		{

		}
		ClipInfo(const std::string& idle, const std::string& move,
			bool flipX, const sf::Vector2f& point) : idle(idle),
			move(move), flipX(flipX), point(point)
		{

		}
	};

protected:
	Animator animator;
	
	sf::Vector2f direction; // 이동하려는 방향 벡터의 점
	float speed = 500.f; // 이동 속도

	std::vector<ClipInfo> clipInfos;
	ClipInfo currentClipInfo;

public:
	AniTest2(const std::string& name = "");
	~AniTest2() override = default;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;


};

