#pragma once

#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn(ObjectManager* objManajer, int dan, int suji, std::string strPlayer);
	~Pawn();

	bool Terminate()override;
	bool Process()override;
	bool Render()override;

};

