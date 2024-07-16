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

	void AddPiece(Piece* piece) { _vPieces.emplace_back(piece); }

private:
	ObjectManager* _objManager;
	// Šl“¾‚µ‚½‹î
	std::vector<Piece*> _vPieces;
};

