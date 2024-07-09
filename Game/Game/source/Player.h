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
	void SelectPiece(int index);
	void MovePiece(int index);

private:
	ObjectManager* _objManager;
	bool _bSelect;
	std::pair<int, int> _saveSquare;
	int _selectedPieceIndex;
};

