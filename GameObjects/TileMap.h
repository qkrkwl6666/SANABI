#pragma once
#include "GameObject.h"
#include "TextGo.h"


class TileMap : public GameObject
{
public:
	enum class TileType
	{
		WALL, // 막히는 벽 갈고리 타지는벽
		PASS, // 통과 가능한 벽 갈고리 X
		WALLNOGRAB , // 벽 && 갈고리 X
	};

	struct Tile
	{
		// 타일 표시 테두리
		sf::RectangleShape shape;
		sf::Texture texture;
		// json저장 용도 나중에 로드할때 이 경로로 각자의 타일 로드 시도해야함
		std::string textureFilePath; 
		TileType type;
		// TODO : 중간에 마우스로 해상도 바꾸면 아웃라이너 깨지는 에러 있음
		// 타일 저장 및 로드 Json 파일로 
		// 타일 로드 할 때 다시 TileType로 변환

		Tile() : type(TileType::PASS)
		{

		}

		Tile(const sf::Vector2f& position,const sf::Vector2f& size, int type)
		{
			shape.setPosition(position);
			shape.setSize(size);
			shape.setFillColor(sf::Color::Black); // 배경색
			shape.setOutlineThickness(0.6f);
			shape.setOutlineColor(sf::Color::White); // 기본 WALL 색깔
			this->type = (TileType)type;
		}
	};

protected:
	std::vector<std::vector<Tile>> tiles;

	sf::Vector2f tileSize; // 타일의 크기
	sf::Vector2i tileMap; // 타일맵 전체 크기
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

