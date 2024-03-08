#include "pch.h"
#include "TileMap.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h" // JSON ���ڿ�ȭ�� ����
#include "rapidjson/filewritestream.h" // ���� ��Ʈ��
#include <cstdio> // C ǥ�� ����� ���� �Լ�
#include <fstream>
#include <Windows.h>
#include <commdlg.h> // ���� ��ȭ ���� �Լ��� ���� ���
#pragma warning(disable : 4996)

TileMap::TileMap(const std::string& name, sf::Vector2f tileSize, sf::Vector2i tileMap)
	: GameObject(name) , tileSize(tileSize) , tileMap(tileMap)
{
	tiles.resize(tileMap.y, std::vector<Tile>(tileMap.x));

	for (int y = 0; y < tileMap.y; ++y)
	{
		for (int x = 0; x < tileMap.x; ++x)
		{
			// �� Ÿ���� ���� ��ġ ���
			sf::Vector2f tilePosition(x * tileSize.x, y * tileSize.y);
			tiles[y][x] = Tile(tilePosition, tileSize, 0);
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
	// ��� Ÿ�Ͽ� ���� �ݺ�
	for (const auto& row : tiles)
	{
		for (const auto& tile : row)
		{
			window.draw(tile.shape); // �� Ÿ���� shape�� �׸���.
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
	if (filePath == tiles[y][x].textureFilePath)
	{
		tiles[y][x].textureFilePath = "";
		tiles[y][x].shape.setTexture(NULL);
		tiles[y][x].shape.setFillColor(sf::Color::Black);
		tiles[y][x].shape.setOutlineThickness(0.5f);
		return;
	}
	tiles[y][x].texture.loadFromFile(filePath);
	tiles[y][x].textureFilePath = filePath;
	tiles[y][x].shape.setTexture(&tiles[y][x].texture);
	tiles[y][x].shape.setFillColor(sf::Color::White);
	tiles[y][x].shape.setOutlineThickness(0.f);
}

void TileMap::SaveTileMap(const std::string& filePath)
{
	using namespace rapidjson;

	rapidjson::Document doc;
	doc.SetObject();
	Document::AllocatorType& allocator = doc.GetAllocator(); // �޸� �Ҵ��� ȹ��

	// Ÿ�ϸ� ũ�� ����
	doc.AddMember("tileSizeX", Value(tileSize.x), allocator);
	doc.AddMember("tileSizeY", Value(tileSize.y), allocator);
	doc.AddMember("mapSizeX", Value(tileMap.x), allocator);
	doc.AddMember("mapSizeY", Value(tileMap.y), allocator);

	// �� Ÿ���� ������ ���� JSON �迭 ��ü ����
	Value tilesArray(kArrayType);

	for (const auto& row : tiles)
	{
		for (const auto& tile : row)
		{
			Value tileObject(kObjectType); // ���� Ÿ�� ������ ���� JSON ��ü ����
			tileObject.AddMember("type", (int)tile.type, allocator); // Ÿ�� Ÿ�� ���� �߰�
			// rapidjson �� std::string ȣȯ�� �ȵǼ� const char* ���� �Ѱ������ 
			// string.c_str() �޼��� �̿��ؼ� �Ѱ��ֱ�
			tileObject.AddMember("texture FilePath", rapidjson::Value(tile.textureFilePath.c_str() , allocator), allocator);
			tileObject.AddMember("x Pos", tile.shape.getPosition().x, allocator);
			tileObject.AddMember("y Pos", tile.shape.getPosition().y, allocator);

			// Ÿ�� ��ü�� Ÿ�� �迭�� �߰�
			tilesArray.PushBack(tileObject, allocator);
		}
	}

	// Ÿ�� �迭�� ����
	doc.AddMember("tiles", tilesArray, allocator);

	// ���� ������ �����ؾ���
	std::wstring savePath = Utils::OpenSaveFileDialog();
	if (savePath.empty())
	{
		return; // ����� ��� return
	}

	// JSON ������ ���Ͽ� ����
	// TODO : fopen �����ϱ�
	std::string sSavePath = Utils::WSTRINGToString(savePath);
	FILE* fp = fopen(sSavePath.c_str(), "wb");

	char writeBuffer[65536];
	FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	PrettyWriter<FileWriteStream> writer(os);
	doc.Accept(writer);
	fclose(fp);
}

