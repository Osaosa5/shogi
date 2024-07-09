#pragma once

#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop(ObjectManager* objManajer, int dan, int suji, std::string strPlayer);
	~Bishop();

	bool Terminate()override;
	bool Process()override;
	bool Render()override;
};

