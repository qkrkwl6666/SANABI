#pragma once
#include "GameObject.h"
#include "TextGo.h"


class TileMap : public GameObject
{
public:
	enum class TileType
	{
		WALL, // ������ �� ���� Ÿ���º�
		PASS, // ��� ������ �� ���� X
		WALLNOGRAB , // �� && ���� X
	};

	struct Tile
	{
		// Ÿ�� ǥ�� �׵θ�
		sf::RectangleShape shape;
		sf::Texture texture;
		// json���� �뵵 ���߿� �ε��Ҷ� �� ��η� ������ Ÿ�� �ε� �õ��ؾ���
		std::string textureFilePath; 
		TileType type;
		// TODO : �߰��� ���콺�� �ػ� �ٲٸ� �ƿ����̳� ������ ���� ����
		// Ÿ�� ���� �� �ε� Json ���Ϸ� 
		// Ÿ�� �ε� �� �� �ٽ� TileType�� ��ȯ

		Tile() : type(TileType::PASS)
		{

		}

		Tile(const sf::Vector2f& position,const sf::Vector2f& size, int type)
		{
			shape.setPosition(position);
			shape.setSize(size);
			shape.setFillColor(sf::Color::Black); // ����
			shape.setOutlineThickness(0.6f);
			shape.setOutlineColor(sf::Color::White); // �⺻ WALL ����
			this->type = (TileType)type;
		}
	};

protected:
	std::vector<std::vector<Tile>> tiles;

	sf::Vector2f tileSize; // Ÿ���� ũ��
	sf::Vector2i tileMap; // Ÿ�ϸ� ��ü ũ��
	wchar_t currentDirectory[256];

public:
	TileMap(const std::string& name);
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

	void SetTileTexture(int y, int x, const std::string& filePath, const TileType& type , bool isRemove = false);
	sf::Vector2f GetTileSize() { return tileSize; }
	sf::Vector2i GetMapSize() { return tileMap; }

	const std::vector<std::vector<Tile>>& GetTiles()
	{
		return tiles;
	}

	void SaveTileMap(const std::string& filePath);
	void LoadTileMap(const std::string& filePath , const float setOutlineThickness);

};

