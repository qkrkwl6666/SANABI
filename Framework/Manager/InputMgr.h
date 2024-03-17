#pragma once

enum class Axis
{
	Horizontal,
	Vertical,
};

struct AxisInfo
{
	Axis axis;

	std::list<sf::Keyboard::Key> positives;
	std::list<sf::Keyboard::Key> negatives;

	float sensi;
	float value;
};

class InputMgr
{
public:
	enum class KEY_STATE
	{
		PRESS,
		DOWN,
		UP
	};
	typedef std::deque<std::pair<sf::Keyboard::Key, KEY_STATE>> SFGM_COMBO;
private:

	InputMgr(const InputMgr&) = delete;
	InputMgr(InputMgr&&) = delete;
	InputMgr& operator=(const InputMgr&) = delete;
	InputMgr& operator=(InputMgr&&) = delete;

	static std::map<Axis, AxisInfo> axisInfoMap;

	static std::list<sf::Keyboard::Key> downList;
	static std::list<sf::Keyboard::Key> upList;
	static std::list<sf::Keyboard::Key> ingList;

	static sf::Vector2f mousePos;

	static SFGM_COMBO combo;
	static float comboTimer;
	static float comboTimeLimit;
	static bool doComboRecord;


public:
	static void Init();

	static void UpdateEvent(const sf::Event& ev);
	static void Update(float dt);

	static void Clear();

	static float GetAxisRaw(Axis axis);	// -1.0 0 1.0
	static float GetAxis(Axis axis);	// -1.0 ~ 1.0
	static bool GetKeyDown(sf::Keyboard::Key key);
	static bool GetKeyUp(sf::Keyboard::Key key);
	static bool GetKey(sf::Keyboard::Key key);

	static sf::Vector2f GetMousePos()
	{
		return mousePos;
	}

	static bool GetMouseButtonDown(sf::Mouse::Button key);
	static bool GetMouseButtonUp(sf::Mouse::Button key);
	static bool GetMouseButton(sf::Mouse::Button key);

	static bool AnyKeyDown();

	static sf::Keyboard::Key MouseButtonToKey(sf::Mouse::Button button)
	{
		return (sf::Keyboard::Key)(button + sf::Keyboard::Key::KeyCount);
	}

	static sf::Mouse::Button KeyToMouseButton(sf::Keyboard::Key key)
	{
		return (sf::Mouse::Button)(key - sf::Keyboard::Key::KeyCount);
	}


	//ÄÞº¸
	static bool IsPerfectCombo(const SFGM_COMBO& combo);
	static bool IsExllentCombo(const SFGM_COMBO& combo);
	static bool IsComboSuccess(const SFGM_COMBO& combo);
	static void ComboRecord(float timeLimit);
	static void StopComboRecord();
	static void ClearCombo();


};

