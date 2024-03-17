#include "pch.h"
#include "GameObject.h"

GameObject::GameObject(const std::string& name)
	: name(name), scene(nullptr)
{
}

GameObject::GameObject(Scene* sc, const std::string& name)
	:name(name), scene(sc)
{
}

GameObject::~GameObject()
{
	Release();
}

void GameObject::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = { 0.f, 0.f };
}

void GameObject::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
}

void GameObject::Init()
{
}

void GameObject::Release()
{
	scene = nullptr;
}

void GameObject::Reset()
{
}

void GameObject::Update(float dt)
{
}

void GameObject::LateUpdate(float dt)
{
}

void GameObject::FixedUpdate(float dt)
{
}

void GameObject::DebugUpdate(float dt)
{
}

void GameObject::Draw(sf::RenderWindow& window)
{
}

void GameObject::DebugDraw(sf::RenderWindow& window)
{
}
