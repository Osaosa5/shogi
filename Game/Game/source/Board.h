#pragma once

#include "Shogi.h"
#include "Square.h"
#include "ObjectManager.h"
#include "Piece.h"

#include "Pawn.h"
#include "Lance.h"
#include "Knight.h"
#include "Silver.h"
#include "Gold.h"
#include "King.h"
#include "Bishop.h"
#include "Rook.h"

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

	Piece* GetPiece(int element) { return _pieces[element]; }
	void SetPiece(int element, Piece* piece) { _pieces[element] = piece; }

	void InitPiece(int element, int tile, int dan, int suji, std::string strPlayer);

private:
	ObjectManager* _objManager;
	Square* _squares[BOARD_TILE];
	Piece* _pieces[BOARD_TILE];
};

