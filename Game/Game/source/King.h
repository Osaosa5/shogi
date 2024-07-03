#pragma once

#include "Piece.h"

class King : public Piece
{
public:
	King(ObjectManager* objManajer, int dan, int suji, PLAYER_TYPE kPlayer);
	~King();

	bool Terminate()override;
	bool Process()override;
	bool Render()override;
};

