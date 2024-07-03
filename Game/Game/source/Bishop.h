#pragma once

#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop(ObjectManager* objManajer, int dan, int suji, PLAYER_TYPE kPlayer);
	~Bishop();

	bool Terminate()override;
	bool Process()override;
	bool Render()override;
};

