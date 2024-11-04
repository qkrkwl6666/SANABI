#pragma once
#include "SpriteGo.h"

class Animator;
class Weapon;
class TileMap;
class Crosshair;
class Enemy;
class BossMajor;

class Player : public SpriteGo
{
public:
	enum class Status
	{
		IDLE,
		CHARGE_DESH,
		ATTACKED,
		TAKE_DOWN,

	};

protected:
	Animator* animator = nullptr;
	Animator* weaponAnimator = nullptr;
	Weapon* weapon = nullptr;
	TileMap* tileMap = nullptr;
	BossMajor* bossMajor = nullptr;

	int hp = 30;
	bool isAttacked = false;
	bool isInvincible = false;

	bool isTakeDown = false;

	float InvincibleDt = 0.f;
	float InvincibleDuration = 3.f;

	std::vector<Enemy*>* enemys;

	float chargeDashSpeed = 1000.f;

	float chargeDashDt = 0.f;
	float chargeDashDuration = 1.f;

	Status currentStatus = Status::IDLE;

	Crosshair* mouse = FRAMEWORK.GetMouse();

	sf::Vector2f WeaponPoint;

	sf::Vector2i PreviewRope = { -1 , -1 };

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
	bool isChargeDashing = false;

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

	sf::Vector2i PreviewRopeFind();

	void Attacked();
	void Dead();
	bool GetIsInvincible() { return isInvincible; }
	void PlayerShiftRolling();

	void PlayerJumping();
	void Delete();

	bool PlayerTileCollisions(float dt);

	void PlayerEnemysCollisions(float dt);

	void HandleRopeSwing(float dt);

	void StartSwing(sf::Vector2i tilePosition);

	bool IsSwinging() {return isSwinging;}

	void SkillCencle();

	sf::Vector2i FindClosestTile();


	void HandleSwingMotion(float dt, float speedFactor);

	void UpdateSwing(float dt);
	void SetStatus(Status status) { currentStatus = status;}
	void SetChargeDash(bool value = false) {isChargeDash = value;}

	void SetCurrentStatus(Status stat) { currentStatus = stat; }
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

		sf::Vector2f anchorToPoint = newPos - ropeAnchorPoint;
    
		float currentLength = std::sqrt(anchorToPoint.x * anchorToPoint.x + anchorToPoint.y * anchorToPoint.y);

		if (currentLength > ropeLength) {
			
			sf::Vector2f normalized = anchorToPoint / currentLength;
			sf::Vector2f clampedPosition = ropeAnchorPoint + normalized * ropeLength;
			return clampedPosition;
		}
    
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


