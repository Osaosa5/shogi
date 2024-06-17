#pragma once

#include "Koma.h"

class SilverGeneral : public Koma
{
public:
	SilverGeneral(ObjectManager* objManajer, VECTOR pos, int dan, int suji, PLAYER_TYPE kPlayer);
	~SilverGeneral();

	bool Terminate()override;
	bool Process()override;
	bool Render()override;
};

