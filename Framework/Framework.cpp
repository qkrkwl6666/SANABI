#include "pch.h"
#include "Framework.h"
#include "Crosshair.h"

void Framework::Init(int width, int height, const std::string& name)
{
	srand(std::time(NULL));

	windowSize.x = width;
	windowSize.y = height;

	window.create(sf::VideoMode(windowSize.x, windowSize.y), name);
	//window.setFramerateLimit(15);
	window.setMouseCursorVisible(false);
	//window.setSize({ 1280, 720 });
	window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width - window.getSize().x) / 2,
		(sf::VideoMode::getDesktopMode().height - window.getSize().y) / 2 ));

	mouse = new Crosshair();
	mouse->Init();

	DT_MGR.Init();
	InputMgr::Init();
	SOUND_MGR.Init();
	SCENE_MGR.Init();
}

void Framework::Do()
{
	while (window.isOpen())
	{
		deltaTime = realDeltaTime = clock.restart();
		deltaTime *= timeScale * isFocus;

		time += deltaTime;
		realTime += realDeltaTime;

		fixedDeltaTime += deltaTime;

		InputMgr::Clear();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F3)
				isDebug = !isDebug;
			InputMgr::UpdateEvent(event);
		}
		InputMgr::Update(GetDT());

		mouse->Update(GetDT());

		if (SCENE_MGR.Update(GetDT()))
		{
			SOUND_MGR.Update(GetDT());
			SCENE_MGR.LateUpdate(GetDT());
			mouse->Update(GetDT());
			mouse->LateUpdate(GetDT());
		}
			
		if (fixedDeltaTime.asSeconds() >= fixedInterval)
		{
			SCENE_MGR.FixedUpdate(fixedDeltaTime.asSeconds());
			mouse->FixedUpdate(GetDT());
			fixedDeltaTime = sf::Time::Zero;
		}
		if (isDebug)
		{
			SCENE_MGR.DebugUpdate(GetDT());
			mouse->DebugUpdate(GetDT());
		}

		window.clear(sf::Color::Black);
		SCENE_MGR.Draw(window);
		mouse->Draw(window);

		window.display();
	}
}

void Framework::Release()
{
	SCENE_MGR.Release();
	SOUND_MGR.Release();

	RES_MGR_TEXTURE.UnloadAll();
	RES_MGR_FONT.UnloadAll();
	RES_MGR_SOUND_BUFFER.UnloadAll();
}
