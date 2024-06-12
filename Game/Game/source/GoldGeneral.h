#pragma once

#include "Koma.h"

class GoldGeneral : public Koma
{
public:
	GoldGeneral(ObjectManager* objManajer, VECTOR pos, PLAYER_TYPE kPlayer);
	~GoldGeneral();

	bool Terminate()override;
	bool Process()override;
	bool Render()override;
};

