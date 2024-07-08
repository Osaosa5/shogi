#pragma once

#include "Shogi.h"
#include "ObjectManager.h"
#include "Piece.h"

class Player : public Shogi
{
public:
	Player(ObjectManager* objManeger, std::string player);
	~Player();

	bool Terminate() override;
	bool Process() override;
	bool Render() override;

	void SelectSquare(int trg);	

private:
	ObjectManager* _objManager;
	bool _bSelect;
	std::pair<int, int> _saveSquare;
};

