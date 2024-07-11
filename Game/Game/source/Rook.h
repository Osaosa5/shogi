#pragma once

#include "Piece.h"

class Rook : public Piece
{
public:
	Rook(ObjectManager* objManajer, int dan, int suji, std::string strPlayer);
	~Rook();

	bool Terminate()override;
	bool Process()override;
	bool Render()override;
};

