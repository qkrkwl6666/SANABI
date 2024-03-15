#pragma once
#include "SpriteGo.h"

class Animator;
class Weapon;
class TileMap;
class Crosshair;
class Enemy;

class Player : public SpriteGo
{
	enum class Status
	{
		IDLE,
		CHARGE_DESH,
		ATTACKED,
	};


protected:
	Animator* animator = nullptr;
	Animator* weaponAnimator = nullptr;
	Weapon* weapon = nullptr;
	TileMap* tileMap = nullptr;

	int hp = 5;
	bool isAttacked = false;

	std::list<Enemy*>* enemys;

	float chargeDashSpeed = 1000.f;

	Status currentStatus = Status::IDLE;

	Crosshair* mouse = FRAMEWORK.GetMouse();

	sf::Vector2f WeaponPoint;

	float gravity = 800.f;
	float speed = 500.f;
	sf::Vector2f velocity; // 속도 // 방향 * speed
	bool isGround = false;
	bool Falling = false;
	bool isJumping = false;

	bool isSwinging = false;
	bool isSwingingAnimation = false;
	bool isShiftRolling = false;
	bool isChargeDash = false;

	bool isCollisions = false;

	float swingForce = 10000.f;
	float maxSwingAngle = 3.14f / 3;

	sf::Vector2f ropeAnchorPoint;
	float ropeLength;

	sf::Vector2i ScreenPos;
	sf::Vector2f worldPos;

	sf::Vector2f playerPos;

	bool isShift = false;
	float isShiftDt = 1.f;
	float deltatime = 0.f;

	int countt = 0;

	float swingAcceleration = 500.f;

	float angularVelocity = 90.f; // 각속도 초기화
	float gravityEffect = 0.f;
	float initialSwingAcceleration = 10.f;
	float maxAngularVelocity = 5.2f; // 허용할 최대 각속도
	float minAngularVelocity = 2.1f;
	float maxTheta = 20.f * (M_PI / 180.f);
	float theta = 0.f;
	float dampingFactor = 0.88f; // 감쇠율
	float lastAngle = 0.f;
	float speedFactor = 0.f;
	int swingDirection = 0; // 스윙 방향: -1(왼쪽), 1(오른쪽), 0(정지)

public:
	Player(const std::string& name = "");
	~Player() override;

	// static void TestStatic();
	// void TestInstance();

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void PlayerAnimationPlay(const std::string& player,
		const std::string& weapon, bool clearQueue = true);

	void Attacked();
	void Dead();

	void PlayerShiftRolling();

	void PlayerJumping();
	void Delete();

	bool PlayerTileCollisions(float dt);

	void PlayerEnemysCollisions(float dt);

	void HandleRopeSwing(float dt);

	void StartSwing(sf::Vector2i tilePosition);

	bool IsSwinging() {return isSwinging;}

	sf::Vector2i FindClosestTile();

	void HandleSwingMotion(float dt, float speedFactor);

	void UpdateSwing(float dt);
	void SetStatus(Status status) { currentStatus = status;}
	void SetChargeDash(bool value = false) {isChargeDash = value;}

	void ClampVelocity(sf::Vector2f& velocity, float minY, float maxY)
	{
		velocity.y = std::max(minY, std::min(velocity.y, maxY));
	}

	sf::Vector2f CalculateSwingForce(const sf::Vector2f& anchorToPoint, float swingAcceleration, float dt)
	{
		// 단진자 운동을 계산하는 로직 추가
		float angle = atan2(anchorToPoint.y, anchorToPoint.x);
		float gravityEffect = -9.81f * sin(angle);
		return sf::Vector2f(cos(angle) * swingAcceleration, sin(angle) * (gravityEffect + swingAcceleration)) * dt;
	}

	sf::Vector2f ClampToRopeLength(const sf::Vector2f& newPos, const sf::Vector2f& ropeAnchorPoint, float ropeLength) {
		// 고정점에서 새 위치까지의 벡터를 계산합니다.
		sf::Vector2f anchorToPoint = newPos - ropeAnchorPoint;
    
		// 벡터의 길이(거리)를 계산합니다.
		float currentLength = std::sqrt(anchorToPoint.x * anchorToPoint.x + anchorToPoint.y * anchorToPoint.y);
    
		// 현재 길이가 로프의 최대 길이보다 큰 경우, 길이를 로프의 최대 길이로 제한합니다.
		if (currentLength > ropeLength) {
			// 벡터를 정규화하고, 로프의 최대 길이를 곱하여 조정된 벡터를 얻습니다.
			sf::Vector2f normalized = anchorToPoint / currentLength;
			sf::Vector2f clampedPosition = ropeAnchorPoint + normalized * ropeLength;
			return clampedPosition;
		}
    
		// 조정이 필요 없는 경우, 원래의 새 위치를 반환합니다.
		return newPos;
	}

	sf::Vector2f CalculateSwingPosition(float angleChange, float length)
	{
		float angleFromVertical = atan2(GetPosition().x - ropeAnchorPoint.x, GetPosition().y - ropeAnchorPoint.y);

		float newAngleFromVertical = angleFromVertical + angleChange;
		sf::Vector2f newPos = {
			ropeAnchorPoint.x + sin(newAngleFromVertical) * length,
			ropeAnchorPoint.y + cos(newAngleFromVertical) * length
		};
		return newPos;
	}

};


