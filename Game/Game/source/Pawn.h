#pragma once

#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn(ObjectManager* objManajer, int dan, int suji, std::string strPlayer);
	~Pawn();

	bool Terminate()override;
	bool Process()override;
	bool Render()override;

	bool Move()override;

	//3d空間に対応した座標
	// 升目に対応した座標
	//オリジナルタイプト裏のやつ
};

