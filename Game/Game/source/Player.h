#pragma once

#include "Shogi.h"
#include "ObjectManager.h"

class Player : public Shogi
{
public:
	Player(ObjectManager* objManeger, std::string player);
	~Player();

	bool Terminate() override;
	bool Process() override;
	bool Render() override;

private:
	ObjectManager* _objManager;
};

