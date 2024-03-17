#pragma once

class SpriteGo : public GameObject
{
protected:
	sf::Sprite sprite;
	std::string textureId;

public:
	SpriteGo(const std::string& name = "");
	SpriteGo(Scene* sc, const std::string& name = "");
	~SpriteGo() override;
	SpriteGo(const SpriteGo&) = delete;
	SpriteGo(SpriteGo&&) = delete;
	SpriteGo& operator=(const SpriteGo&) = delete;
	SpriteGo& operator=(SpriteGo&&) = delete;

	void SetTexture(const std::string& textureId);
	void SetTexture();

	void SetPosition(const sf::Vector2f& pos) override;
	void Translate(const sf::Vector2f& pos) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetRotation(float r) override;
	void SetFlipX(bool filp) override;
	void SetFlipY(bool filp) override;

	void Draw(sf::RenderWindow& window) override;
	void Reset() override;

	sf::Sprite* GetSprite() { return &sprite; }

	inline const sf::FloatRect GetLocalBounds() const { return sprite.getLocalBounds(); }
	inline const sf::FloatRect GetGlobalBounds() const { return sprite.getGlobalBounds(); }
};

