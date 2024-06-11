#pragma once

#include "Shogi.h"
#include "ObjectManager.h"
#include "ShogiBan.h"

class Koma : public Shogi
{
public:
	Koma(ObjectManager* objManajer, VECTOR pos, PLAYER_TYPE kPlayer);
	virtual ~Koma();

	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	virtual bool Move();
	void HitTest();

private:
	ObjectManager* _objManajer;
	VECTOR _oldPos;
};

