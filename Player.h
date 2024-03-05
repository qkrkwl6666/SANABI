#pragma once
#include "SpriteGo.h"

class Player : public SpriteGo
{
protected:

public:
	Player(const std::string& name = "");
	~Player();
};

