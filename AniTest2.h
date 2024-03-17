#pragma once

#include "SpriteGo.h"
#include "Animator.h"

class AniTest2 : public SpriteGo
{
	//�ִϸ��̼� ���� �˻� ����ü
public:
	struct ClipInfo // AnimationClipInfo
	{
		std::string idle;
		std::string move;
		bool flipX = false;
		sf::Vector2f point; // �� ����Ʈ

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
	
	sf::Vector2f direction; // �̵��Ϸ��� ���� ������ ��
	float speed = 500.f; // �̵� �ӵ�

	std::vector<ClipInfo> clipInfos;
	ClipInfo currentClipInfo;

public:
	AniTest2(const std::string& name = "");
	~AniTest2() override = default;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;


};

