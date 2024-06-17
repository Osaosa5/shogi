#pragma once

#include "Koma.h"

class Knight : public Koma
{
public:
	Knight(ObjectManager* objManajer, VECTOR pos, int dan, int suji, PLAYER_TYPE kPlayer);
	~Knight();

	bool Terminate()override;
	bool Process()override;
	bool Render()override;
};

