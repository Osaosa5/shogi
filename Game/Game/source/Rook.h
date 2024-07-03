#pragma once

#include "Piece.h"

class Rook : public Piece
{
public:
	Rook(ObjectManager* objManajer, int dan, int suji, PLAYER_TYPE kPlayer);
	~Rook();

	bool Terminate()override;
	bool Process()override;
	bool Render()override;
};

