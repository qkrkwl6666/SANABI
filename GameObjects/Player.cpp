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
	// TODO : �÷��̾� sortLayer �ϸ� �ñ�� �������� 
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

	/*auto* clip = animator->GetClip("Player_Run_Landing");
	clip->fps = 30;*/
	
	//animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("data/Animations/Run.csv"));
}

void Player::Reset()
{
	animator->ClearEvent();

	//std::function<void()> funcInstance = std::bind(&Player::PlayerFalling, this);
	//std::function<void()> funcInstance2 = std::bind(&Player::PlayerJumping, this);
	//animator->AddEvent("Player_Fall_Start", 2, funcInstance);
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

	ScreenPos = SCENE_MGR.GetCurrentScene()->UiToScreen((sf::Vector2f)mouse->GetPosition());
	worldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld((sf::Vector2i)ScreenPos);

	HandleRopeSwing(dt);

	float h = InputMgr::GetAxisRaw(Axis::Horizontal); // - 1 0 1

	// ���� ����
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		isGround = false;
		animator->Play("Player_Jumping");
		weaponAnimator->Play("Player_Arm_Jumping");
		velocity.y = -500.f;
	}

	//std::cout << velocity.x << std::endl;

	// �ӵ��� ���� ���� ���ӵ� ���� ����
	float speedFactor = std::abs(velocity.x) / speed; // ���� �ӵ��� �ִ� �ӵ��� ���� ����

	if (!isSwinging)
	{
		velocity.x = h * speed;
		if (!isGround)
		{
			velocity.y += gravity * dt; // �߷� ����
		}
	}
	else
	{
		if (abs(h) > 0)
		{
			swingAcceleration += h * swingForce * speedFactor * dt; // ���� ���ӵ��� �ӵ� ����� ����
		}
	}

	if (isSwinging)
	{
		HandleSwingMotion(dt, speedFactor);
	}
	else
	{
		position += velocity * dt;
	}

	SetPosition(position);

	//if (velocity.y > 100.f && !isGround && !Falling)
	//{
	//	animator->Play("Player_Falling");
	//	weaponAnimator->Play("Player_Arm_Falling");
	//	Falling = true;
	//}

	//if (position.y > FRAMEWORK.GetWindowSize().y * 0.5f)
	//{
	//	isGround = true;
	//	position.y = FRAMEWORK.GetWindowSize().y * 0.5f;
	//	velocity.y = 0.f;
	//}

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
		WeaponPoint = { -30.f , -30.f };
	}
	else
	{
		WeaponPoint = { 30.f , - 30.f};
	}

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

	//TODO : Player_Run_Start ������ > Player_Running �����ϱ�

	else if ((animator->GetCurrentClipId() == "Player_Jumping" || 
		animator->GetCurrentClipId() == "Player_Falling") && isGround)
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
	}

	weapon->SetPosition(GetPosition() + WeaponPoint);
}

void Player::LateUpdate(float dt)
{
	SpriteGo::LateUpdate(dt);

	//std::cout << GetPosition().y << std::endl;

	// ���߿� �ִ� ���ȿ��� Ÿ�� �浹 �˻� ����
	PlayerTileCollisions(dt);

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

void Player::PlayerFalling()
{
	std::cout << "Player_Falling!!" << std::endl;
	animator->Play("Player_Falling");
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

void Player::PlayerTileCollisions(float dt)
{
	// �÷��̾��� ���� �ٴ� ��ġ ���
	float predictedBottom = GetPosition().y + GetGlobalBounds().height / 2 + velocity.y * dt;

	// �ٴڸ� �ٷ� �Ʒ��� Ÿ�� �ε��� ���
	sf::Vector2i predictedTileIndex = {
		static_cast<int>(GetPosition().x / tileMap->GetTileSize().x),
		static_cast<int>((predictedBottom + 1) / tileMap->GetTileSize().y)
	};

	// Ÿ�� �ε����� Ÿ�ϸ� ���� ���� �ִ��� Ȯ��
	if (predictedTileIndex.x >= 0 && predictedTileIndex.x < tileMap->GetMapSize().x && predictedTileIndex.y >= 0 && predictedTileIndex.y < tileMap->GetMapSize().y)
	{
		if (tileMap->GetTiles()[predictedTileIndex.y][predictedTileIndex.x].type == TileMap::TileType::WALL)
		{
			// ���� �ٴ� ��ġ�� Ÿ���� ��ܺ��� �Ʒ��� �ִٸ�, �÷��̾ Ÿ���� ���� �ø�
			float tileTop = predictedTileIndex.y * tileMap->GetTileSize().y;
			SetPosition({ GetPosition().x, tileTop - GetGlobalBounds().height / 2 });
			velocity.y = 0;
			isGround = true;
		}
		else
		{
			isGround = false;
		}
	}
}

void Player::HandleRopeSwing(float dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isSwinging)
	{
		angularVelocity = 0.0f; // ���� ���� �� ���ӵ� �ʱ�ȭ
		sf::Vector2i closestTile = FindClosestTile();
		if (closestTile != sf::Vector2i(-1, -1))
		{
			StartSwing(closestTile);
			// ���� ���� �� �ʱ� velocity.y ���� ����

			velocity.y = std::max(velocity.y, -300.f); // ���� ���� �� �ʱ� ��·��� �ο�
		}
	}

	if (isSwinging)
	{
		UpdateSwing(dt); // ���� �� ������Ʈ
	}

	if (!isSwinging) return;

	sf::Vector2f anchorToPoint = GetPosition() - ropeAnchorPoint;
	float angle = atan2(anchorToPoint.y, anchorToPoint.x);

	// ���� ���ӵ� ����
	if (InputMgr::GetKeyDown(sf::Keyboard::A))
	{
		swingAcceleration -= swingForce * dt;
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::D))
	{
		swingAcceleration += swingForce * dt;
	}

	// ���� �� velocity ����
	velocity += CalculateSwingForce(anchorToPoint, swingAcceleration, dt);
	ClampVelocity(velocity, -500.f, 500.f); // velocity.y�� �ִ�/�ּڰ� ����

	// ������ ���̸� ����Ͽ� ��ġ ����
	sf::Vector2f correctedPos = ClampToRopeLength(GetPosition() + velocity * dt, ropeAnchorPoint, ropeLength);
	SetPosition(correctedPos);

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && isSwinging)
	{
		// ���� ���� ����
		isSwinging = false;
		swingAcceleration = 0; // ���� �ߴ� �� ���ӵ� �ʱ�ȭ

		// ������ Ǯ���� ���� velocity.y ����
		// ���� ���, velocity.y�� ��� (�ϰ� ��)�� ���, ��� ȿ���� �ֱ� ���� ���� ����
		if (velocity.y > 0)
		{
			// ��� ȿ���� ���� velocity.y ����
			// �� ���� ������ �ʿ信 ���� ���� ����
			velocity.y = -250; // ���� ��, ��Ȳ�� ���� ���� �ʿ�
		}
	}
}

void Player::StartSwing(sf::Vector2i tilePosition)
{
	isSwinging = true;
	ropeAnchorPoint = sf::Vector2f(tilePosition.x * tileMap->GetTileSize().x, tilePosition.y * tileMap->GetTileSize().y);
	ropeLength = Utils::Distance(GetPosition(), ropeAnchorPoint); // ���� ���� �ʱ�ȭ
	swingAcceleration = initialSwingAcceleration; // ���� ���ӵ� �ʱ�ȭ
	swingDirection = 0; // ���� ���� �ʱ�ȭ
}

sf::Vector2i Player::FindClosestTile()
{
	sf::Vector2i closestTileIndex(-1, -1); // �ʱⰪ�� ��ȿ���� ���� �ε����� ����
	float closestDistance = std::numeric_limits<float>::max();

	// ���콺 ��ġ�� ���� Ÿ�� ��ǥ ���
	int mouseTileX = static_cast<int>(worldPos.x / tileMap->GetTileSize().x);
	int mouseTileY = static_cast<int>(worldPos.y / tileMap->GetTileSize().y);

	// ���콺 ��ġ �ֺ��� 9�� Ÿ���� �˻�
	for (int y = mouseTileY - 1; y <= mouseTileY + 1; ++y)
	{
		for (int x = mouseTileX - 1; x <= mouseTileX + 1; ++x)
		{
			// �˻� ������ Ÿ�ϸ� ���� �ִ��� Ȯ��
			if (x >= 0 && x < tileMap->GetMapSize().x && y >= 0 && y < tileMap->GetMapSize().y)
			{
				// PASS�� �ƴ� Ÿ�Ͽ��� ������ �� �� ����
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

	// ��ȿ�� Ÿ���� ������ (-1, -1) ��ȯ
	return closestTileIndex;
}

void Player::HandleSwingMotion(float dt, float speedFactor)
{
	sf::Vector2f anchorToPoint = GetPosition() - ropeAnchorPoint;
	float angle = atan2(anchorToPoint.y, anchorToPoint.x);

	// �߷� ���ӵ� ����
	float gravityEffect = -9.81f * sin(angle) * (1 + speedFactor); // �ӵ� ����� ����� �߷� ȿ�� ����

	float totalAcceleration = gravityEffect + swingAcceleration;
	velocity += sf::Vector2f(cos(angle), sin(angle)) * totalAcceleration * dt;

	// ������ ���̸� ����Ͽ� ��ġ ����
	sf::Vector2f newPos = GetPosition() + velocity * dt;
	sf::Vector2f correctedPos = ropeAnchorPoint + Utils::GetNormalize(newPos - ropeAnchorPoint) * ropeLength;
	SetPosition(correctedPos);

}

void Player::UpdateSwing(float dt)
{
	if (!isSwinging) return;

	sf::Vector2f anchorToPoint = GetPosition() - ropeAnchorPoint;
	float angle = atan2(anchorToPoint.y, anchorToPoint.x);

	// �÷��̾� �Է¿� ���� ���� ���ӵ� ����
	if (InputMgr::GetKeyDown(sf::Keyboard::A))
	{
		swingAcceleration -= swingForce * dt; // �������� ���� ����
		swingDirection = -1;
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::D))
	{
		swingAcceleration += swingForce * dt; // ���������� ���� ����
		swingDirection = 1;
	}

	// ���� ���⿡ ���� ��ġ ������Ʈ
	float swingSpeed = swingAcceleration * swingDirection;
	sf::Vector2f movement = Utils::GetNormalize(anchorToPoint) * swingSpeed * dt;
	SetPosition(GetPosition() + movement);

	// ���� ����
	swingAcceleration *= dampingFactor;
}
