#pragma once

#include "Shogi.h"
#include "Square.h"
#include "ObjectManager.h"
#include "Piece.h"

class Board : public Shogi
{
public:
	Board(ObjectManager* objManager);
	~Board();

	bool Terminate() override;
	bool Process() override;
	bool Render() override;

	Square* GetSquare(int element) { return _squares[element]; }
	void SetSquare(int element, Square* square) { _squares[element] = square; }

private:
	ObjectManager* _objManager;
	Square* _squares[BOARD_TILE];
	Piece* _pieces[BOARD_TILE];
};

