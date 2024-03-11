#pragma once
#include "GameObject.h"

class TextGo : public GameObject
{
public:
	sf::Text text;
	TextGo(const std::string& name = "");
	TextGo(Scene* sc, const std::string& name = "");
	~TextGo() override = default;
	//TextGo(const TextGo&) = delete;
	//TextGo(TextGo&&) = delete;
	//TextGo& operator=(const TextGo&) = delete;
	//TextGo& operator=(TextGo&&) = delete;

	void SetString(const std::string& str);
	void SetString(const std::wstring& str);

	void Set(const sf::Font& texture, const std::string& str, int size, const sf::Color& color);
	void Set(const sf::Font& texture, const std::wstring& str, int size, const sf::Color& color);

	void SetFont(const std::string& textureId);
	void SetFont(const sf::Font& texture);

	void SetPosition(const sf::Vector2f& pos) override;
	void Translate(const sf::Vector2f& delta) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetRotation(float r) override;
	void SetFlipX(bool filp) override;
	void SetFlipY(bool filp) override;

	void SetCharacterSize(int size);
	void SetColor(sf::Color color);
	void SetOutLine(float thick, sf::Color color);

	sf::FloatRect GetGlobalBounds();
	std::string GetString() { return text.getString(); }

	void Draw(sf::RenderWindow& window) override;

};
