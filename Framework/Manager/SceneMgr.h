#pragma once
#include "Singleton.h"

class Scene;

enum class SceneIds
{
	None = -1,
	SceneTitle,
	SceneGame,
	SceneTileEditer,
	Count
};

class SceneMgr : public Singleton<SceneMgr>
{
	friend class Singleton<SceneMgr>;

protected:
	std::vector<Scene*> scenes;

	SceneIds startScene = SceneIds::SceneTitle;
	SceneIds currentScene = startScene;
	SceneIds nextScene = SceneIds::None;

	SceneMgr() = default;
	virtual ~SceneMgr();

public:
	void Init();
	void Release();

	void ChangeScene(SceneIds id);

	Scene* GetCurrentScene() { return scenes[(int)currentScene]; }
	Scene* GetScene(SceneIds id) { return scenes[(int)id]; }

	bool Update(float dt);
	void LateUpdate(float dt);
	void FixedUpdate(float dt);
	void DebugUpdate(float dt);
	void Draw(sf::RenderWindow& window);
	void DebugDraw(sf::RenderWindow& window);

	SceneMgr(const SceneMgr&) = delete;
	SceneMgr(SceneMgr&&) = delete;
	SceneMgr& operator=(const SceneMgr&) = delete;
	SceneMgr& operator=(SceneMgr&&) = delete;
};

#define SCENE_MGR (SceneMgr::Instance())