#pragma once

#include "Object.h"
#include "Shogi.h"
#include "ObjectManager.h"
#include "Piece.h"

#include "appframe.h"

class PieceStand : public Shogi
{
public:
	PieceStand(ObjectManager* objManajer, VECTOR pos, std::string player);
	~PieceStand();

	bool Terminate() override;
	bool Process() override;
	bool Render() override;

	void AddPiece(Piece* piece) { _vHasPieces.emplace_back(piece); }

	// セッター・ゲッター
	std::vector<Piece*> GetVPieces() const { return _vHasPieces; }
	void SetVPieces(std::vector<Piece*> vPieces) { _vHasPieces = vPieces; }

private:
	ObjectManager* _objManager;
	// 獲得した駒
	std::vector<Piece*> _vHasPieces;
};

