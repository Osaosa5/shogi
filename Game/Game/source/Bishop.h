#pragma once

#include "Koma.h"

class Bishop : public Koma
{
public:
	Bishop(ObjectManager* objManajer, int dan, int suji, PLAYER_TYPE kPlayer);
	~Bishop();

	bool Terminate()override;
	bool Process()override;
	bool Render()override;
};

