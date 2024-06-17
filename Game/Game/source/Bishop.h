#pragma once

#include "Koma.h"

class Bishop : public Koma
{
public:
	Bishop(ObjectManager* objManajer, VECTOR pos, int dan, int suji, PLAYER_TYPE kPlayer);
	~Bishop();

	bool Terminate()override;
	bool Process()override;
	bool Render()override;
};

