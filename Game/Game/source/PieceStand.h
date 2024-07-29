#pragma once

#include "Object.h"
#include "Shogi.h"
#include "ObjectManager.h"
#include "Piece.h"

#include "appframe.h"

class PieceStand : public Shogi
{
public:
	enum class GET_PIECE_TYPE
	{
		Pawn,
		Lance,
		Knight,
		Silver,
		Gold,
		Bishop,
		Rook
	};

private:
	using vPtrSquares	= std::vector<Square*>;
	using vPtrPieces	= std::vector<Piece*>;
	using mPtrPieces = std::unordered_map < GET_PIECE_TYPE, std::unordered_set<Piece*> > ;

public:
	PieceStand(ObjectManager* objManajer, VECTOR pos, std::string player);
	~PieceStand();

	bool Initialize()	override;
	bool Terminate()	override;
	bool Process()		override;
	bool Render()		override;

	void AddPiece(Piece* piece) { _vHasPieces.emplace_back(piece); }

	// セッター・ゲッター
	Square* 	GetSquare(int index) const				{ return _vSquares[index]; }
	void		SetSquare(int index, Square* square)	{ _vSquares[index] = square; }

	Piece*		GetPiece(int index) const			{ return _vHasPieces[index]; }
	void		SetPiece(int index, Piece* piece)	{ _vHasPieces[index] = piece; }
	vPtrPieces	GetVPieces() const					{ return _vHasPieces; }
	void		SetVPieces(vPtrPieces vPieces)		{ _vHasPieces = vPieces; }
		
private:
	ObjectManager*	_objManager;

	// 駒台のマス
	vPtrSquares		_vSquares;
	// 獲得した駒
	vPtrPieces		_vHasPieces;

	mPtrPieces		_mHasPieces;
};	

