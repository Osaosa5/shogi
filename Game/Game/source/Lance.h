#pragma once

#include "Koma.h"

class Lance : public Koma
{
public:
	Lance(ObjectManager* objManajer, VECTOR pos, PLAYER_TYPE kPlayer);
	~Lance();

	bool Terminate()override;
	bool Process()override;
	bool Render()override;
};
