#pragma once

#include "Koma.h"

class King : public Koma
{
public:
	King(ObjectManager* objManajer, VECTOR pos, PLAYER_TYPE kPlayer);
	~King();

	bool Terminate()override;
	bool Process()override;
	bool Render()override;
};

