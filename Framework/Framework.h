#pragma once
#include "Singleton.h"
#include "RenderWindowRBR.h"

// 1. �ʱ�ȭ / ���η��� / ����
// 2. �ð� ���� ��� / ������ ����
// 3. ...Mgr 

class UIDebug;
class Crosshair;

class Framework : public Singleton<Framework>
{
	friend Singleton<Framework>;

protected:
	Framework() = default;
	virtual ~Framework() = default;

	sf::Vector2i windowSize;
	RenderWindowRBR window;
	float fixedInterval = 1.f/60.f;
	Crosshair* mouse;

	sf::Clock clock;
	float timeScale = 1.f;

	sf::Time realTime; // ���� ���ۺ��� ��� �ð�
	sf::Time time; // ���� ���ۺ��� ��� �ð� (timeScale �����...)

	sf::Time realDeltaTime;
	sf::Time deltaTime;

	sf::Time fixedDeltaTime;

	bool isFocus = true;


	//�����
	UIDebug* uiDebug;
	bool isDebug = false;

public:
	sf::RenderWindow& GetWindow() { return window; }	// !!
	const sf::Vector2i& GetWindowSize() const { return windowSize; }

	float GetRealTime() const { return realTime.asSeconds(); }
	float GetTime() const { return time.asSeconds(); }
	float GetRealDT() const { return realDeltaTime.asSeconds(); }
	float GetDT() const { return deltaTime.asSeconds(); }
	
	float GetTimeScale() const { return timeScale; }
	void SetTimeScale(float scale) { timeScale = scale; }

	UIDebug* GetDebug() const { return uiDebug; }

	Crosshair* GetMouse() { return mouse; }

	virtual void Init(int width, int height, const std::string& name = "Game");
	virtual void Do();
	virtual void Release();

};

#define FRAMEWORK (Singleton<Framework>::Instance())
