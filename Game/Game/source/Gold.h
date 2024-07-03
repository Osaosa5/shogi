#pragma once

#include "Piece.h"

class Gold : public Piece
{
public:
	Gold(ObjectManager* objManajer, int dan, int suji, PLAYER_TYPE kPlayer);
	~Gold();

	bool Terminate()override;
	bool Process()override;
	bool Render()override;
};

