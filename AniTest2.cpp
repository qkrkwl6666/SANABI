#include "pch.h"
#include "AniTest2.h"

AniTest2::AniTest2(const std::string& name)
	: SpriteGo(name) 
{
	
}

void AniTest2::Init()
{
	std::string textureId = "graphics/Untitled.png";
	int width = 256;
	int height = 256;

	animator.SetTarget(&sprite);

	clipInfos.push_back({"data/Animations/IdleSide.csv" ,  "data/Animations/MoveSide.csv" , false , 
		Utils::GetNormalize({-1, -1 })});
	clipInfos.push_back({ "data/Animations/IdleUp.csv" ,   "data/Animations/MoveUp.csv" , false ,
		Utils::GetNormalize({0, -1 }) });
	clipInfos.push_back({ "data/Animations/IdleSide.csv" , "data/Animations/MoveSide.csv" , true ,
		Utils::GetNormalize({1, -1 }) });

	clipInfos.push_back({ "data/Animations/IdleSide.csv" , "data/Animations/MoveSide.csv" , false ,
		Utils::GetNormalize({-1, 0 }) });				   
	clipInfos.push_back({ "data/Animations/IdleSide.csv" , "data/Animations/MoveSide.csv" , true ,
		Utils::GetNormalize({1, 0 }) });				   
														   
	clipInfos.push_back({ "data/Animations/IdleSide.csv" , "data/Animations/MoveSide.csv" , false ,
		Utils::GetNormalize({-1, 1 }) });				   
	clipInfos.push_back({ "data/Animations/IdleDown.csv" , "data/Animations/MoveDown.csv" , false ,
		Utils::GetNormalize({0, 1 }) });				   
	clipInfos.push_back({ "data/Animations/IdleSide.csv" , "data/Animations/MoveSide.csv" , true ,
		Utils::GetNormalize({1, 1 }) });

}

void AniTest2::Reset()
{
	animator.Play("data/Animations/IdleDown.csv");
	SetOrigin(Origins::MC);
	SetPosition({ FRAMEWORK.GetWindowSize().x * 0.5f ,
	FRAMEWORK.GetWindowSize().y * 0.5f });
	SetFlipX(false);

	currentClipInfo = clipInfos[6];
}

void AniTest2::Update(float dt)
{
	animator.Update(dt);

	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);

	// Magnitude ���� 
	float mag = Utils::Magnitude(direction); 

	// ���̰� 1���� ũ�ٸ� ����ȭ
	if (mag > 1.f)
	{
		direction /= mag;
	}

	Translate(direction * speed * dt);

	if (direction.x != 0.f || direction.y != 0.f)
	{
		// �����̳��߿��� ���� ������ ���� std::min_element
		auto min = std::min_element(clipInfos.begin() , clipInfos.end() ,
			[this](const ClipInfo& lhs, const ClipInfo& rhs)
			{
				return Utils::Distance(direction, lhs.point) < 
					Utils::Distance(direction, rhs.point);
			});
		// ���� ����� ���� ã�Ƽ� ����
		currentClipInfo = *min;
	}
	SetFlipX(currentClipInfo.flipX);

	// x y ��ȭ�� ������ move false�� idle
	const std::string& clipId = (direction.x != 0.f || direction.y != 0.f) ?
		currentClipInfo.move : currentClipInfo.idle;

	if (animator.GetCurrentClipId() != clipId)
	{
		animator.Play(clipId);
	}
	
}
