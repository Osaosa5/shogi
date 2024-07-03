#pragma once

#include "Piece.h"

class Lance : public Piece
{
public:
	Lance(ObjectManager* objManajer, int dan, int suji, PLAYER_TYPE kPlayer);
	~Lance();

	bool Terminate()override;
	bool Process()override;
	bool Render()override;
};

