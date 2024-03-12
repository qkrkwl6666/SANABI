#include "pch.h"
#include "Player.h"
#include "Animator.h"
#include "AniTest2.h"
#include "Weapon.h"
#include "TileMap.h"
#include "SceneGame.h"
#include "Crosshair.h"

Player::Player(const std::string& name)
	:SpriteGo(name)
{

}

Player::~Player()
{
	Delete();
}

//void Player::TestStatic()
//{
//	std::cout << "TestStatic" << std::endl;
//}
//
//void Player::TestInstance()
//{
//	std::cout << "TestInstance" << std::endl;
//}

void Player::Init()
{
	// TODO : 플레이어 sortLayer 하면 팅기는 현상있음 
	SpriteGo::Init();
	animator = new Animator();
	animator->SetTarget(&sprite);

	weapon = new Weapon("Weapon");
	SCENE_MGR.GetScene(SceneIds::SceneTitle)->AddGo(weapon);

	weapon->Init();
	weapon->Reset();

	SetScale({ 3.f , 3.f });

	SetOrigin(Origins::MC);

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Idle.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Running.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Jumping.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Run_Landing.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Fall_Start.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Falling.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Run_Stop.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Run_Start.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Ceiling_Stick_Idle.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Ceiling_Stick_Moving.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Player_Shift_Rolling.csv"));
	weapon->SetOrigin(Origins::MC);
	/*auto* clip = animator->GetClip("Player_Run_Landing");
	clip->fps = 30;*/
	
	//animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Run.csv"));
}

void Player::Reset()
{
	animator->ClearEvent();

	std::function<void()> funcInstanceShiftRolling = std::bind(&Player::PlayerShiftRolling, this);
	animator->AddEvent("Player_Shift_Rolling", 10, funcInstanceShiftRolling);

	//std::function<void()> funcInstance2 = std::bind(&Player::PlayerJumping, this);
	//animator->AddEvent("Player_Falling", 2, funcInstance2);

	//std::function<void()> funcStatic = std::bind(&Player::TestStatic);
	//animator.AddEvent("data/Idle.csv", 5, funcStatic);

	/*PlayerAnimationPlay("data/Animations/Player_Idle.csv",
		"data/Animations/Player_Arm_Idle.csv");*/

	tileMap = dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetTileMap();

	weaponAnimator = weapon->GetAnimator();

	animator->Play("Player_Idle");
	weaponAnimator->Play("Player_Arm_Idle");

	WeaponPoint = { GetPosition().x - 30, GetPosition().y + 30 };

	weapon->SetPosition(WeaponPoint);

	SetOrigin(Origins::MC);
	SetPosition({ FRAMEWORK.GetWindowSize().x * 0.5f ,
		FRAMEWORK.GetWindowSize().y * 0.6f });
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);
	animator->Update(dt);
	weapon->Update(dt);

	// TODO : 무기 UPDATE 안되는 에러있음 강제 호출중

	ScreenPos = SCENE_MGR.GetCurrentScene()->UiToScreen((sf::Vector2f)mouse->GetPosition());
	worldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld((sf::Vector2i)ScreenPos);
	HandleRopeSwing(dt);

	//std::cout << velocity.y << std::endl;
	//std::cout << isGround << std::endl;

	float h = InputMgr::GetAxisRaw(Axis::Horizontal); // - 1 0 1

	// 점프 시작
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		isGround = false;
		animator->Play("Player_Jumping");
		weaponAnimator->Play("Player_Arm_Jumping");
		velocity.y = -500.f;
	}

	//std::cout << swingAcceleration << std::endl;

	// 속도에 따른 스윙 가속도 증가 로직
	speedFactor = std::abs(velocity.x) / speed; // 현재 속도를 최대 속도로 나눈 비율

	if (!isSwinging)
	{
		velocity.x = h * speed;
		if (!isGround)
		{
			velocity.y += gravity * dt; // 중력 적용
		}
	}
	else
	{
		if (abs(h) > 0)
		{
			swingAcceleration += h * swingForce * speedFactor * dt; // 스윙 가속도에 속도 계수를 적용
		}
	}

	if (isSwinging)
	{
		HandleSwingMotion(dt, speedFactor);

		//if (!isSwingingAnimation)
		//{
		//	animator->Play("Player_Ceiling_Stick_Moving");
		//	isSwingingAnimation = true;
		//}
	}
	else
	{
		//Translate(velocity * dt);
		position += velocity * dt;
	}
	PlayerTileCollisions(dt);
	SetPosition(position);

	if (velocity.y > 100.f && !isGround && !Falling && !isSwinging && !isShiftRolling)
	{
		animator->Play("Player_Falling");
		weaponAnimator->Play("Player_Arm_Falling");
		Falling = true;
		isSwingingAnimation = false;
	}

	if (!animator->IsPlaying())
	{
		animator->Play("Player_Idle");
		weaponAnimator->Play("Player_Arm_Idle");
	}

	if (h != 0.f)
	{
		SetFlipX(h < 0);
		weapon->SetFlipX(h < 0);
	}

	if (!weapon->GetFlipX())
	{
		WeaponPoint = { -10.f , 0.f };
	}
	else
	{
		WeaponPoint = { 10.f , 0.f};
	}

	{
		if (animator->GetCurrentClipId() == "Player_Idle")
		{
			if (h != 0.f)
			{
				animator->Play("Player_Running");
				weaponAnimator->Play("Player_Arm_Running");
			}
		}

		else if (animator->GetCurrentClipId() == "Player_Running")
		{
			if (h == 0.f)
			{
				animator->Play("Player_Run_Stop");
				weaponAnimator->Play("Player_Arm_Run_Stop");
			}
		}

		//TODO : Player_Run_Start 실행후 > Player_Running 실행하기

		else if ((animator->GetCurrentClipId() == "Player_Jumping" || 
					animator->GetCurrentClipId() == "Player_Falling" ||  
					animator->GetCurrentClipId() == "Player_Ceiling_Stick_Moving") && isGround)
		{
			if (h == 0.f)
			{
				animator->Play("Player_Idle");
				weaponAnimator->Play("Player_Arm_Idle");
			}
			else
			{
				animator->Play("Player_Running");
				weaponAnimator->Play("Player_Arm_Running");
			}
			Falling = false;
			isSwingingAnimation = false;
			isShiftRolling = false;
		}

	}

	if (!isSwinging)
	{
		weapon->SetPosition(GetPosition() + WeaponPoint);
	}

	else if (isSwinging)
	{
		weapon->SetPosition(ropeAnchorPoint);
	}
}

void Player::LateUpdate(float dt)
{
	SpriteGo::LateUpdate(dt);

	//std::cout << GetPosition().y << std::endl;

	// 공중에 있는 동안에는 타일 충돌 검사 수행
	//PlayerTileCollisions(dt);

}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	weapon->Draw(window);

	if (isSwinging)
	{
		sf::VertexArray ropeLine(sf::Lines, 2);
		ropeLine[0].position = sf::Vector2f(ropeAnchorPoint);
		ropeLine[1].position = GetPosition();
		ropeLine[0].color = sf::Color::White;
		ropeLine[1].color = sf::Color::White;

		window.draw(ropeLine);
	}
}

void Player::PlayerAnimationPlay(const std::string& player, const std::string& weapon, bool clearQueue)
{
	animator->Play(player , clearQueue);
	weaponAnimator->Play(weapon , clearQueue);
}

void Player::PlayerShiftRolling()
{
	std::cout << "PlayerShiftRolling!!" << std::endl;
	isShiftRolling = false;
	//animator->Play("PlayerShiftRolling");
}

void Player::PlayerJumping()
{
	std::cout << "Player_Jumping!!" << std::endl;
	animator->Play("Player_Jumping");
}

void Player::Delete()
{
	if (animator != nullptr)
	{
		delete animator;
		animator = nullptr;
	}
}

bool Player::PlayerTileCollisions(float dt)
{
	// 현재 플레이어 위치의 타일맵 인덱스 계산
	sf::Vector2i tileIndex = { (int)GetPosition().x / (int)tileMap->GetTileSize().x ,
		(int)GetPosition().y / (int)tileMap->GetTileSize().y };

	if (tileIndex.x >= 1 && tileIndex.x < tileMap->GetMapSize().x - 1 &&
		tileIndex.y >= 1 && tileIndex.y < tileMap->GetMapSize().y - 1)
	{
		// 하단 타일
	// 플레이어의 하단 타일
		sf::Vector2i bottomIndex = { tileIndex.x , tileIndex.y + 1 };

		if (tileMap->GetTiles()[bottomIndex.y][bottomIndex.x].type == TileMap::TileType::WALL)
		{
			if (GetPosition().y + (GetGlobalBounds().height / 2) >
				tileMap->GetTiles()[bottomIndex.y][bottomIndex.x].shape.getGlobalBounds().top)
			{
				SetPosition({ GetPosition().x ,tileMap->GetTiles()
					[bottomIndex.y][bottomIndex.x].shape.getGlobalBounds().top -
					(GetGlobalBounds().height / 2) });
				std::cout << GetPosition().y << std::endl;
				isGround = true;
				velocity.y = 0.f;
				return true;
			}
		}
		else if (tileMap->GetTiles()[bottomIndex.y + 1][bottomIndex.x].type != TileMap::TileType::WALL)
		{
			isGround = false;
		}

		// 플레이어의 위쪽 타일
		sf::Vector2i TopIndex = { tileIndex.x , tileIndex.y - 1 };

		if (tileMap->GetTiles()[TopIndex.y][TopIndex.x].type == TileMap::TileType::WALL)
		{
			if (GetPosition().y + (GetGlobalBounds().height / 2) <
				tileMap->GetTiles()[bottomIndex.y][bottomIndex.x].shape.getGlobalBounds().top
				+ tileMap->GetTiles()[bottomIndex.y][bottomIndex.x].shape.getGlobalBounds().height)
			{
				SetPosition({ GetPosition().x ,tileMap->GetTiles()[bottomIndex.y][bottomIndex.x].shape.getGlobalBounds().top
				+ tileMap->GetTiles()[bottomIndex.y][bottomIndex.x].shape.getGlobalBounds().height -
					(GetGlobalBounds().height / 2) });;
				return true;
			}
		}

		// 플레이어의 오른쪽 타일
		sf::Vector2i RightIndex = { tileIndex.x + 1 , tileIndex.y };

		if (tileMap->GetTiles()[RightIndex.y][RightIndex.x].type == TileMap::TileType::WALL)
		{
			if (GetPosition().x + (GetGlobalBounds().width / 2) >
				tileMap->GetTiles()[RightIndex.y][RightIndex.x].shape.getGlobalBounds().left)
			{
				SetPosition({ tileMap->GetTiles()[RightIndex.y][RightIndex.x].
					shape.getGlobalBounds().left - (GetGlobalBounds().width / 2) ,
					GetPosition().y });
				return false;
			}
		}

		sf::Vector2i LeftIndex = { tileIndex.x - 1 , tileIndex.y };

		if (tileMap->GetTiles()[LeftIndex.y][LeftIndex.x].type == TileMap::TileType::WALL)
		{
			if (GetPosition().x - (GetGlobalBounds().width / 2) <
				tileMap->GetTiles()[LeftIndex.y][LeftIndex.x].shape.getGlobalBounds().left
				+ tileMap->GetTiles()[LeftIndex.y][LeftIndex.x].shape.getGlobalBounds().width)
			{
				SetPosition({ tileMap->GetTiles()[LeftIndex.y][LeftIndex.x].
					shape.getGlobalBounds().left + tileMap->GetTiles()[LeftIndex.y][LeftIndex.x].
					shape.getGlobalBounds().width + (GetGlobalBounds().width / 2) ,
					GetPosition().y });
				return false;
			}
		}
	}

	//// 플레이어의 예상 바닥 위치 계산
	//float predictedBottom = GetPosition().y + 
	//	GetGlobalBounds().height / 2 + velocity.y * dt;

	//// 바닥면 바로 아래의 타일 인덱스 계산
	//sf::Vector2i predictedTileIndex = {
	//	static_cast<int>(GetPosition().x / tileMap->GetTileSize().x),
	//	static_cast<int>((predictedBottom + 1) / tileMap->GetTileSize().y)
	//};

	//// 타일 인덱스가 타일맵 범위 내에 있는지 확인
	//if (predictedTileIndex.x >= 0 && predictedTileIndex.x < tileMap->GetMapSize().x && predictedTileIndex.y >= 0 && predictedTileIndex.y < tileMap->GetMapSize().y)
	//{
	//	if (tileMap->GetTiles()[predictedTileIndex.y][predictedTileIndex.x].type == TileMap::TileType::WALL
	//		&& !isJumping)
	//	{
	//		// 예상 바닥 위치가 타일의 상단보다 아래에 있다면, 플레이어를 타일의 위로 올림
	//		float tileTop = predictedTileIndex.y * tileMap->GetTileSize().y;
	//		SetPosition({ GetPosition().x, tileTop - GetGlobalBounds().height / 2 });
	//		velocity.y = 0;
	//		isGround = true;
	//	}
	//	else
	//	{
	//		isGround = false;
	//	}
	//}
}

void Player::HandleRopeSwing(float dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isSwinging)
	{
		angularVelocity = 0.0f; // 스윙 시작 시 각속도 초기화
		sf::Vector2i closestTile = FindClosestTile();
		if (closestTile != sf::Vector2i(-1, -1))
		{
			StartSwing(closestTile);
			animator->Play("Player_Ceiling_Stick_Moving");
			weaponAnimator->Play("Player_Arm_CeilingStick_Moving");
			// 스윙 시작 시 초기 velocity.y 값을 설정

			velocity.y = std::max(velocity.y, -300.f); // 스윙 시작 시 초기 상승력을 부여
		}
	}

	if (isSwinging)
	{
		UpdateSwing(dt); // 스윙 중 업데이트
	}

	if (!isSwinging) return;

	sf::Vector2f anchorToPoint = GetPosition() - ropeAnchorPoint;
	float angle = atan2(anchorToPoint.y, anchorToPoint.x);

	// 스윙 가속도 조절
	if (InputMgr::GetKeyDown(sf::Keyboard::A))
	{
		swingAcceleration -= swingForce * dt;
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::D))
	{
		swingAcceleration += swingForce * dt;
	}

	// 스윙 중 velocity 조절
	velocity += CalculateSwingForce(anchorToPoint, swingAcceleration, dt);
	ClampVelocity(velocity, -500.f, 500.f); // velocity.y의 최대/최솟값 제한

	// 로프의 길이를 고려하여 위치 보정
	sf::Vector2f correctedPos = ClampToRopeLength(GetPosition() + velocity * dt, ropeAnchorPoint, ropeLength);
	SetPosition(correctedPos);

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && isSwinging)
	{
		// 스윙 종료 로직
		isSwinging = false;

		{
			if (swingAcceleration >= 350.f && swingAcceleration <= 10000.f && !isShiftRolling)
			{
				animator->Play("Player_Shift_Rolling");
				weaponAnimator->Play("Player_Arm_Shift_Rolling");
			}
			else if (swingAcceleration <= -350.f && swingAcceleration >= -10000.f && !isShiftRolling)
			{
				animator->Play("Player_Shift_Rolling");
				weaponAnimator->Play("Player_Arm_Shift_Rolling");
			}
			else
			{
				animator->Play("Player_Falling");
				weaponAnimator->Play("Player_Arm_Falling");
			}

		}

		swingAcceleration = 0; // 스윙 중단 시 가속도 초기화

		// 스윙을 풀었을 때의 velocity.y 조정
		// 예를 들어, velocity.y가 양수 (하강 중)일 경우, 상승 효과를 주기 위해 값을 조정
		if (velocity.y > 0)
		{
			// 상승 효과를 위한 velocity.y 조정
			// 이 값은 게임의 필요에 따라 조절 가능
			velocity.y = -250; // 예시 값, 상황에 따라 조절 필요
		}
	}
}

void Player::StartSwing(sf::Vector2i tilePosition)
{
	isSwinging = true;
	ropeAnchorPoint = sf::Vector2f(tilePosition.x * tileMap->GetTileSize().x, tilePosition.y * tileMap->GetTileSize().y);
	ropeLength = Utils::Distance(GetPosition(), ropeAnchorPoint); // 로프 길이 초기화
	swingAcceleration = initialSwingAcceleration; // 스윙 가속도 초기화
	swingDirection = 0; // 스윙 방향 초기화
}

sf::Vector2i Player::FindClosestTile()
{
	sf::Vector2i closestTileIndex(-1, -1); // 초기값을 유효하지 않은 인덱스로 설정
	float closestDistance = std::numeric_limits<float>::max();

	// 마우스 위치에 대한 타일 좌표 계산
	int mouseTileX = static_cast<int>(worldPos.x / tileMap->GetTileSize().x);
	int mouseTileY = static_cast<int>(worldPos.y / tileMap->GetTileSize().y);

	// 마우스 위치 주변의 9개 타일을 검사
	for (int y = mouseTileY - 1; y <= mouseTileY + 1; ++y)
	{
		for (int x = mouseTileX - 1; x <= mouseTileX + 1; ++x)
		{
			// 검사 범위가 타일맵 내에 있는지 확인
			if (x >= 0 && x < tileMap->GetMapSize().x && y >= 0 && y < tileMap->GetMapSize().y)
			{
				// PASS가 아닌 타일에만 로프를 걸 수 있음
				if (tileMap->GetTiles()[y][x].type != TileMap::TileType::PASS)
				{
					sf::Vector2f tileCenter(x * tileMap->GetTileSize().x + tileMap->GetTileSize().x / 2,
						y * tileMap->GetTileSize().y + tileMap->GetTileSize().y / 2);
					float distance = Utils::Distance(worldPos, tileCenter);
					if (distance < closestDistance)
					{
						closestDistance = distance;
						closestTileIndex = sf::Vector2i(x, y);
					}
				}
			}
		}
	}

	// 유효한 타일이 없으면 (-1, -1) 반환
	return closestTileIndex;
}

void Player::HandleSwingMotion(float dt, float speedFactor)
{
	sf::Vector2f anchorToPoint = GetPosition() - ropeAnchorPoint;
	float angle = atan2(anchorToPoint.y, anchorToPoint.x);

	// 중력 가속도 조정
	float gravityEffect = -9.81f * sin(angle) * (1 + speedFactor); // 속도 계수를 사용해 중력 효과 증가

	float totalAcceleration = gravityEffect + swingAcceleration;
	velocity += sf::Vector2f(cos(angle), sin(angle)) * totalAcceleration * dt;

	// 로프의 길이를 고려하여 위치 보정
	sf::Vector2f newPos = GetPosition() + velocity * dt;
	sf::Vector2f correctedPos = ropeAnchorPoint + Utils::GetNormalize(newPos - ropeAnchorPoint) * ropeLength;
	SetPosition(correctedPos);

}

void Player::UpdateSwing(float dt)
{
	if (!isSwinging) return;

	sf::Vector2f anchorToPoint = GetPosition() - ropeAnchorPoint;
	float angle = atan2(anchorToPoint.y, anchorToPoint.x);

	// 플레이어 입력에 따른 스윙 가속도 조절
	if (InputMgr::GetKeyDown(sf::Keyboard::A))
	{
		swingAcceleration -= swingForce * dt; // 왼쪽으로 스윙 가속
		swingDirection = -1;
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::D))
	{
		swingAcceleration += swingForce * dt; // 오른쪽으로 스윙 가속
		swingDirection = 1;
	}

	// 스윙 방향에 따라 위치 업데이트
	float swingSpeed = swingAcceleration * swingDirection;
	sf::Vector2f movement = Utils::GetNormalize(anchorToPoint) * swingSpeed * dt;
	SetPosition(GetPosition() + movement);

	// 감쇠 적용
	swingAcceleration *= dampingFactor;
}
