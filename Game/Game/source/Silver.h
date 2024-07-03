#pragma once

#include "Piece.h"

class Silver : public Piece
{
public:
	Silver(ObjectManager* objManajer, int dan, int suji, PLAYER_TYPE kPlayer);
	~Silver();

	bool Terminate()override;
	bool Process()override;
	bool Render()override;
};

