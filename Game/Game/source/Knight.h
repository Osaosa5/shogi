#pragma once

#include "Piece.h"

class Knight : public Piece
{
public:
	Knight(ObjectManager* objManajer, int dan, int suji, PLAYER_TYPE kPlayer);
	~Knight();

	bool Terminate()override;
	bool Process()override;
	bool Render()override;
};

