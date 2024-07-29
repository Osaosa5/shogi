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
	using vPtrSquares = std::vector<Square*>;
	using vPtrPieces = std::vector<Piece*>;
public:
	Board(ObjectManager* objManager);
	~Board();

	bool Terminate()	override;
	bool Process()		override;
	bool Render()		override;

	Square* GetSquare(int element)					{ return _vHasSquares[element]; }
	void	SetSquare(int element, Square* square)	{ _vHasSquares[element] = square; }

	Piece*	GetPiece(int element)				{ return _vHasPieces[element]; }
	void	SetPiece(int element, Piece* piece) { _vHasPieces[element] = piece; }

	void	InitPiece(int element, int tile, int dan, int suji, std::string strPlayer);

private:
	ObjectManager*	_objManager;

	vPtrSquares		_vHasSquares;
	vPtrPieces		_vHasPieces;
};

