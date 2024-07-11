#pragma once

#include "Piece.h"

class Lance : public Piece
{
public:
	Lance(ObjectManager* objManajer, int dan, int suji, std::string strPlayer);
	~Lance();

	bool Terminate()override;
	bool Process()override;
	bool Render()override;
};

