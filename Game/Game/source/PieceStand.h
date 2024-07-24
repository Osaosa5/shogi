#pragma once

#include "Object.h"
#include "Shogi.h"
#include "ObjectManager.h"
#include "Piece.h"

#include "appframe.h"

class PieceStand : public Shogi
{
	using vPtrSquares	= std::vector<Square*>;
	using vPtrPieces	= std::vector<Piece*>;
public:
	PieceStand(ObjectManager* objManajer, VECTOR pos, std::string player);
	~PieceStand();

	bool Initialize()	override;
	bool Terminate()	override;
	bool Process()		override;
	bool Render()		override;

	void AddPiece(Piece* piece) { _vHasPieces.emplace_back(piece); }

	// �Z�b�^�[�E�Q�b�^�[
	vPtrPieces	GetVPieces() const				{ return _vHasPieces; }
	void		SetVPieces(vPtrPieces vPieces)	{ _vHasPieces = vPieces; }

private:
	ObjectManager* _objManager;

	// ���̃}�X
	vPtrSquares	_vSquares;
	// �l��������
	vPtrPieces	_vHasPieces;
};

