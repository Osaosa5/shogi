#pragma once

#include "Shogi.h"

#include "ObjectManager.h"
#include "Board.h"

class Koma : public Shogi
{
public:
	Koma(ObjectManager* objManajer, VECTOR pos, int dan, int suji, PLAYER_TYPE kPlayer);
	virtual ~Koma();

	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	virtual bool Move();
	void HitTest();
	bool GetBoard();
	void SetKomaCentralTile();

protected:
	VECTOR _oldPos;

private:
	ObjectManager* _objManajer;
	Board* _board;

};

