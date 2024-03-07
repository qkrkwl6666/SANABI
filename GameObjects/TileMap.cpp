#include "pch.h"
#include "TileMap.h"

TileMap::TileMap(const std::string& name, sf::Vector2f tileSize, sf::Vector2i tileMap)
	: GameObject(name) , tileSize(tileSize) , tileMap(tileMap)
{
	tiles.resize(tileMap.y , 
		std::vector<TileMap::Tile>(tileMap.x , 
			Tile({ 0, 0 } , tileSize, 0)));

	for (int y = 0; y < tileMap.y; y++)
	{
		for (int x = 0; x < tileMap.x; x++)
		{
			tiles[y][x] = Tile(sf::Vector2f(x * tileSize.x, y * tileSize.y), tileSize, 0);
		}
	}
}

void TileMap::Init()
{
	GameObject::Init();


}

void TileMap::Release()
{
	GameObject::Release();
}

void TileMap::Reset()
{
	GameObject::Reset();
}

void TileMap::Update(float dt)
{
	GameObject::Update(dt);

}

void TileMap::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
	// 모든 타일에 대해 반복
	for (const auto& row : tiles)
	{
		for (const auto& tile : row)
		{
			window.draw(tile.shape); // 각 타일의 shape를 그린다.
		}
	}
}

void TileMap::SetOrigin(Origins preset)
{

}

void TileMap::SetOrigin(const sf::Vector2f& newOrigin)
{

}

void TileMap::Translate(const sf::Vector2f& delta)
{
	GameObject::Translate(delta);
	
}

void TileMap::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
}

void TileMap::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	GameObject::SetScale(scale);

}

void TileMap::SetRotation(float r)
{
	GameObject::SetRotation(r);

}

void TileMap::SetFlipX(bool flip)
{
	GameObject::SetFlipX(flip);

}

void TileMap::SetFlipY(bool flip)
{
	GameObject::SetFlipY(flip);
	
}

void TileMap::SetTileTexture(int y, int x, const std::string& filePath)
{
	tiles[y][x].texture.loadFromFile(filePath);
	tiles[y][x].shape.setTexture(&tiles[y][x].texture);
	tiles[y][x].shape.setFillColor(sf::Color::White);
}

