#pragma once

#include "Piece.h"

class Knight : public Piece
{
public:
	Knight(ObjectManager* objManajer, int dan, int suji, std::string strPlayer);
	~Knight();

	bool Terminate()override;
	bool Process()override;
	bool Render()override;
};

