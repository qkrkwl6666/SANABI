#pragma once
#include "GameObject.h"

class TileMap : public GameObject
{
public:
	struct Tile
	{
		// Ÿ�� ǥ�� �׵θ�
		sf::RectangleShape shape;
		sf::Texture texture;
		// json���� �뵵 ���߿� �ε��Ҷ� �� ��η� ������ Ÿ�� �ε� �õ��ؾ���
		std::string textureFilePath; 
		int type;
		// TODO : �߰��� ���콺�� �ػ� �ٲٸ� �ƿ����̳� ������ ���� ����
		// Ÿ�� ���� �� �ε� Json ���Ϸ� 
		Tile() : type(0)
		{

		}
		Tile(const sf::Vector2f& position,const sf::Vector2f& size, int type)
		{
			shape.setPosition(position);
			shape.setSize(size);
			shape.setFillColor(sf::Color::Black); // ����
			shape.setOutlineThickness(0.5f); 
			shape.setOutlineColor(sf::Color::White);
			this->type = type;
		}
	};

protected:
	std::vector<std::vector<Tile>> tiles;
	sf::Vector2f tileSize; // Ÿ���� ũ��
	sf::Vector2i tileMap; // Ÿ�ϸ� ��ü ũ��

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

	void SetTileTexture(int y , int x , const std::string& filePath);
	sf::Vector2f GetTileSize() { return tileSize; }
	sf::Vector2i GetMapSize() { return tileMap; }

	void SaveTileMap(const std::string& filePath);
};

