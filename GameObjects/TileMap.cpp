#include "pch.h"
#include "TileMap.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h" // JSON 문자열화를 위함
#include "rapidjson/filewritestream.h" // 파일 스트림
#include <cstdio> // C 표준 입출력 관련 함수
#include <fstream>
#include <Windows.h>
#include <commdlg.h> // 공통 대화 상자 함수를 위한 헤더
#pragma warning(disable : 4996)

TileMap::TileMap(const std::string& name, sf::Vector2f tileSize, sf::Vector2i tileMap)
	: GameObject(name) , tileSize(tileSize) , tileMap(tileMap)
{
	tiles.resize(tileMap.y, std::vector<Tile>(tileMap.x));

	for (int y = 0; y < tileMap.y; ++y)
	{
		for (int x = 0; x < tileMap.x; ++x)
		{
			// 각 타일의 실제 위치 계산
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
	Document::AllocatorType& allocator = doc.GetAllocator(); // 메모리 할당자 획득

	// 타일맵 크기 저장
	doc.AddMember("tileSizeX", Value(tileSize.x), allocator);
	doc.AddMember("tileSizeY", Value(tileSize.y), allocator);
	doc.AddMember("mapSizeX", Value(tileMap.x), allocator);
	doc.AddMember("mapSizeY", Value(tileMap.y), allocator);

	// 각 타일의 정보를 담을 JSON 배열 객체 생성
	Value tilesArray(kArrayType);

	for (const auto& row : tiles)
	{
		for (const auto& tile : row)
		{
			Value tileObject(kObjectType); // 개별 타일 정보를 담을 JSON 객체 생성
			tileObject.AddMember("type", (int)tile.type, allocator); // 타일 타입 정보 추가
			// rapidjson 은 std::string 호환이 안되서 const char* 으로 넘겨줘야함 
			// string.c_str() 메서드 이용해서 넘겨주기
			tileObject.AddMember("texture FilePath", rapidjson::Value(tile.textureFilePath.c_str() , allocator), allocator);
			tileObject.AddMember("x Pos", tile.shape.getPosition().x, allocator);
			tileObject.AddMember("y Pos", tile.shape.getPosition().y, allocator);

			// 타일 객체를 타일 배열에 추가
			tilesArray.PushBack(tileObject, allocator);
		}
	}

	// 타일 배열들 저장
	doc.AddMember("tiles", tilesArray, allocator);

	// 이제 파일을 저장해야함
	std::wstring savePath = Utils::OpenSaveFileDialog();
	if (savePath.empty())
	{
		return; // 취소할 경우 return
	}

	// JSON 문서를 파일에 쓰기
	// TODO : fopen 수정하기
	std::string sSavePath = Utils::WSTRINGToString(savePath);
	FILE* fp = fopen(sSavePath.c_str(), "wb");

	char writeBuffer[65536];
	FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	PrettyWriter<FileWriteStream> writer(os);
	doc.Accept(writer);
	fclose(fp);
}

