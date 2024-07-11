#pragma once

#include "Piece.h"

class King : public Piece
{
public:
	King(ObjectManager* objManajer, int dan, int suji, std::string strPlayer);
	~King();

	bool Terminate()override;
	bool Process()override;
	bool Render()override;
};

