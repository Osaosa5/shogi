#pragma once

#include "Koma.h"

class GoldGeneral : public Koma
{
public:
	GoldGeneral(ObjectManager* objManajer, VECTOR pos, int dan, int suji, PLAYER_TYPE kPlayer);
	~GoldGeneral();

	bool Terminate()override;
	bool Process()override;
	bool Render()override;
};

