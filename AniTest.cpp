#include "pch.h"
#include "AniTest.h"
#include "Animator.h"
#include "AniTest2.h"

AniTest::AniTest(const std::string& name)
	:SpriteGo(name)
{

}

void AniTest::TestStatic()
{
	std::cout << "TestStatic" << std::endl;
}

void AniTest::TestInstance()
{
	std::cout << "TestInstance" << std::endl;
}

void AniTest::Init()
{
	SpriteGo::Init();

	animator.SetTarget(&sprite);

	/*animator.AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Idle.csv"));
	animator.AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Jump.csv"));
	animator.AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Run.csv"));*/
}

void AniTest::Reset()
{
	animator.ClearEvent();

	//std::function<void()> funcInstance = std::bind(&AniTest::TestInstance, this);
	//animator.AddEvent("data/Jump.csv", 5, funcInstance);
	//
	//std::function<void()> funcStatic = std::bind(&AniTest::TestStatic);
	//animator.AddEvent("data/Idle.csv", 5, funcStatic);


	animator.Play("Data/Player_Idle.csv");
	SetOrigin(Origins::MC);
	SetPosition({ FRAMEWORK.GetWindowSize().x * 0.5f ,
		FRAMEWORK.GetWindowSize().y * 0.5f });
}

void AniTest::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);
	
	float h = InputMgr::GetAxisRaw(Axis::Horizontal); // - 1 0 1

	if (isGround && InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		isGround = false;
		animator.Play("Data/Player_Idle.csv");
		velocity.y = -500.f;
	}

	velocity.x = h * speed;
	velocity.y += gravity * dt;
	position += velocity * dt;

	if (position.y > FRAMEWORK.GetWindowSize().y * 0.5f)
	{
		isGround = true;
		position.y = FRAMEWORK.GetWindowSize().y * 0.5f;
		velocity.y = 0.f;
	}

	SetPosition(position);

	if (h != 0.f)
	{
		SetFlipX(h < 0);
	}

	if (animator.GetCurrentClipId() == "Data/Player_Idle.csv")
	{
		if (h != 0.f)
		{
			animator.Play("Data/Player_Idle.csv");
		}
	}
	else if (animator.GetCurrentClipId() == "Data/Player_Idle.csv")
	{
		if (h == 0.f)
		{
			animator.Play("Data/Player_Idle.csv");
		}

	}

	else if (animator.GetCurrentClipId() == "Data/Player_Idle.csv" && isGround)
	{
		if (h == 0.f)
		{
			animator.Play("Data/Player_Idle.csv");
		}
		else
		{
			animator.Play("Data/Player_Idle.csv");
		}
	}
}
