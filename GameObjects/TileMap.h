#pragma once
#include "GameObject.h"
class TileMap : public GameObject
{
protected:
	std::string spriteSheetId;
	sf::Texture* texture;

	sf::Vector2i cellCount;
	sf::Vector2f cellSize;

	sf::Transform transform;

	sf::Vector2f boundaryLT;
	sf::Vector2f boundaryRB;

public:
	sf::VertexArray va;
	TileMap(const std::string& name = "name");
	~TileMap() = default;

	TileMap(const TileMap&) = delete;
	TileMap(TileMap&&) = delete;
	TileMap& operator=(const TileMap&) = delete;
	TileMap& operator=(TileMap&&) = delete;

	void Set(const sf::Vector2i& count, const sf::Vector2f& size);
	void SetSpriteSheetId(const std::string& id);
	void UpdateTransform();

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;



	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetRotation(float r) override;
	void Translate(const sf::Vector2f& delta) override;
	void SetBoundary();
	std::pair<const sf::Vector2f&, const sf::Vector2f&> GetBoundary() const;

	void SetFlipX(bool flip) override;
	void SetFlipY(bool flip) override;

	sf::FloatRect GetLocalBoundsT() const;
	sf::FloatRect GetGlobalBoundsT() const;
};

