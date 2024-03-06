#pragma once
#include "GameObject.h"


class TileMap : public GameObject
{
public:
	struct Tile
	{
		// 타일 표시 테두리
		sf::RectangleShape shape;
		sf::Texture* texture;
		int type;

		Tile(sf::Vector2f position, sf::Vector2f size, int type)
		{
			shape.setPosition(position);
			shape.setSize(size);
			shape.setFillColor(sf::Color::White);
			this->type = type;
		}
	};

protected:
	std::vector<std::vector<Tile>> tiles;
	sf::Vector2f tileSize; // 타일의 크기
	sf::Vector2i tileMap; // 타일맵 전체 크기

public:
	TileMap(const std::string& name, 
		sf::Vector2f tileSize , sf::Vector2i tileMap);
	~TileMap() = default;

	TileMap(const TileMap&) = delete;
	TileMap(TileMap&&) = delete;
	TileMap& operator=(const TileMap&) = delete;
	TileMap& operator=(TileMap&&) = delete;

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

	void SetFlipX(bool flip) override;
	void SetFlipY(bool flip) override;


};

