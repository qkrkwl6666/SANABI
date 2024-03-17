#pragma once

class GameObject
{
protected:
	Scene* scene;

	bool active = true;
	int tag = -1;

	Origins originPreset = Origins::TL;
	sf::Vector2f origin = { 0.f, 0.f };
	sf::Vector2f position = { 0.f, 0.f };
	sf::Vector2f scale = { 1.f, 1.f };
	float rotation = 0.f;
	
	bool isFlipX = false;
	bool isFlipY = false;

public:
	std::string name = "";
	int sortLayer = 0;
	int sortOrder = 0;

	GameObject(const std::string& name = "");
	GameObject(Scene* sc, const std::string& name = "");
	virtual ~GameObject();
	GameObject(const GameObject&) = delete;
	GameObject(GameObject&&) = delete;
	GameObject& operator=(const GameObject&) = delete;
	GameObject& operator=(GameObject&&) = delete;

	static bool CompareDrawOrder(const GameObject* lhs, const GameObject* rhs)
	{
		if (lhs->sortLayer != rhs->sortLayer)
			return lhs->sortLayer < rhs->sortLayer;
		return lhs->sortOrder < rhs->sortOrder;
	}
	static bool CompareeDrawOrder(const GameObject& lhs, const GameObject& rhs)
	{
		if (lhs.sortLayer != rhs.sortLayer)
			return lhs.sortLayer < rhs.sortLayer;
		return lhs.sortOrder < rhs.sortOrder;
	}

	inline bool operator<(const GameObject& rhs)
	{
		if (sortLayer != rhs.sortLayer)
			return sortLayer < rhs.sortLayer;
		return sortOrder < rhs.sortOrder;
	}

	virtual void SetActive(bool active) { this->active = active; }
	virtual bool GetActive() {return active;}

	virtual void SetOrigin(Origins preset);
	virtual inline void SetOrigin(const sf::Vector2f& newOrigin)
	{
		originPreset = Origins::Custom;
		origin = newOrigin;
	}
	virtual void SetPosition(const sf::Vector2f& pos) { position = pos; }

	virtual void SetScale(const sf::Vector2f& scale);
	virtual void SetFlipX(bool flip) {  isFlipX = flip ; }
	virtual void SetFlipY(bool flip) { isFlipY = flip; }
	virtual void SetRotation(float r) { rotation = r; }
	virtual void Translate(const sf::Vector2f& delta) { position += delta; }
	inline void SetScene(Scene* sc) { scene = sc; }
	inline Scene* GetScene() const { return scene; }

	virtual void Init();
	virtual void Release();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void LateUpdate(float dt);
	virtual void FixedUpdate(float dt);
	virtual void DebugUpdate(float dt);
	virtual void Draw(sf::RenderWindow& window);
	virtual void DebugDraw(sf::RenderWindow& window);

	bool GetActive() const { return active; }

	sf::Vector2f GetOrigin() const { return origin; }
	sf::Vector2f GetPosition() const { return position; }

	sf::Vector2f GetScale() const { return scale; }
	bool GetFlipX() const { return isFlipX; }
	bool GetFlipY() const { return isFlipY; }
	float GetRotation() const { return rotation; }
	int GetTag() const { return tag; }

};

