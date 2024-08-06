#pragma once

#include "appframe.h"

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

#include <iostream>

class Board : public Shogi
{
	using vPtrSquares	= std::vector<Square*>;
	using vPtrPieces	= std::vector<Piece*>;
public:
	Board(ObjectManager* objManager);
	~Board();

	bool Terminate()	override;
	bool Process()		override;
	bool Render()		override;

	Square*		GetSquare(int index)					{ return _vHasSquares[index]; }
	void		SetSquare(int index, Square* square)	{ _vHasSquares[index] = square; }
	vPtrSquares GetSquares() const						{ return _vHasSquares; }

	Piece*	GetPiece(int index)				{ return _vHasPieces[index]; }
	void	SetPiece(int index, Piece* piece) 
	{
		if (index < 0 || index >= _vHasPieces.size()) 
		{
			std::cerr << "Index out of range: " << index << std::endl;
			return;
		}
		_vHasPieces[index] = piece;
	}
	vPtrPieces GetPieces() const			{ return _vHasPieces; }

	void	InitPiece(int index, int tile, int dan, int suji, std::string strPlayer);

private:
	ObjectManager*	_ptrObjManager;

	vPtrSquares		_vHasSquares;
	vPtrPieces		_vHasPieces;
};

