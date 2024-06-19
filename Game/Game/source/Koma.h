#pragma once

#include "Shogi.h"

#include "ObjectManager.h"
#include "Board.h"
#include "Square.h"

class Koma : public Shogi
{
public:
	Koma(ObjectManager* objManajer, int dan, int suji, PLAYER_TYPE kPlayer);
	virtual ~Koma();

	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	virtual bool Move();
	void HitTest();
	bool GetBoard();
	class Square* GetSquarePutKoma();
	void SetKomaCentralTile();
	void SetKomaToSquare();

protected:
	VECTOR _oldPos;
	bool _bSetPos;

private:
	ObjectManager* _objManager;
	Board* _board;

};

