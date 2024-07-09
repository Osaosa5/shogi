#pragma once

#include "Shogi.h"
#include "ObjectManager.h"
#include "Piece.h"
#include "ModeGame.h"

class Player : public Shogi
{
public:
	Player(ObjectManager* objManeger, std::string player, ModeGame* game);
	~Player();

	bool Terminate() override;
	bool Process() override;
	bool Render() override;

	void SelectSquare(int trg);	
	void SelectPiece(int index);
	void MovePiece(int index);

private:
	ObjectManager* _objManager;
	ModeGame* _game;
	std::vector<Piece*> _vHasPieces;
	int _selectedPieceIndex;
};

