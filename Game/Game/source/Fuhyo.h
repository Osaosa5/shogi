#pragma once

#include "Koma.h"

class Fuhyo : public Koma
{
public:
	Fuhyo(ObjectManager* objManajer, VECTOR pos);
	~Fuhyo();

	bool Terminate()override;
	bool Process()override;
	bool Render()override;

	bool Move()override;

	//3d空間に対応した座標
	// 升目に対応した座標
	//オリジナルタイプト裏のやつ
};

