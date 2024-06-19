#pragma once

#include "Shogi.h"
#include "ObjectManager.h"
#include "Square.h"
#include "Board.h"

class Player : public Shogi
{
public:
	Player(ObjectManager* objManeger, std::string player);
	~Player();

	bool Terminate() override;
	bool Process() override;
	bool Render() override;

	Square* GetSquare(int dan, int suji);
	Board* GetBoard();

private:
	ObjectManager* _objManager;
	bool _bSelect;
	// _selectSquare->(dan, suji)
	std::pair<int, int> _selectSquare;
};

