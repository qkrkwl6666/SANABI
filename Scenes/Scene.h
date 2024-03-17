#pragma once

class GameObject;

class Scene
{
protected:
	SceneIds id;
	std::list<GameObject*> gameObjects;
	std::list<GameObject*> uiObjects;
	std::deque<GameObject*> deleteDeque;
	std::list<GameObject*> sortList;

	sf::View worldView;
	sf::View uiView;

	ResourceMgr<sf::Texture>& texResMgr;
	ResourceMgr<sf::Font>& fontResMgr;
	ResourceMgr<sf::SoundBuffer>& soundResMgr;
public:
	enum Layers
	{
		None = 0,
		World = 1,
		Ui = 2,
		EveryThing = 0xFFFFFFFF,
	};

	Scene(SceneIds id);
	virtual ~Scene() = default;

	sf::Vector2f ScreenToWorld(sf::Vector2i screenPos);
	sf::Vector2i WorldTOScreen(sf::Vector2f worldPos);
	sf::Vector2f ScreenToUi(sf::Vector2i screenPos);
	sf::Vector2i UiToScreen(sf::Vector2f uiPos);

	virtual void Init();
	virtual void Release();
	virtual void Reset();

	virtual void Enter();
	virtual void Exit();

	virtual void Update(float dt);
	virtual void LateUpdate(float dt);
	virtual void FixedUpdate(float dt);
	virtual void DebugUpdate(float dt);
	virtual void Draw(sf::RenderWindow& window);
	virtual void DebugDraw(sf::RenderWindow& window);

	virtual GameObject* FindGo(const std::string& name, Layers layer = Layers::EveryThing);
	int FindGoAll(const std::string& name, std::list<GameObject*>& list, Layers layer = Layers::EveryThing);

	virtual GameObject* AddGo(GameObject* obj, Layers layer = Layers::World);

	virtual void RemoveGo(GameObject* obj);
	virtual void DeleteGo(GameObject* obj);
	virtual void ReSoltGo(GameObject* obj);

	sf::View& GetWorldView();
	sf::View& GetUiView();

	const sf::Vector2f& GetViewCenter()
	{
		return worldView.getCenter();
	}

	Scene(const Scene&) = delete;
	Scene(Scene&&) = delete;
	Scene& operator=(const Scene&) = delete;
	Scene& operator=(Scene&&) = delete;
};

