#pragma once

#include "Koma.h"

class Rook : public Koma
{
public:
	Rook(ObjectManager* objManajer, VECTOR pos, PLAYER_TYPE kPlayer);
	~Rook();

	bool Terminate()override;
	bool Process()override;
	bool Render()override;
};

