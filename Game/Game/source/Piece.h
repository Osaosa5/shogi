#pragma once

#include "Shogi.h"

#include "ObjectManager.h"
#include "Square.h"

class Piece : public Shogi
{
public:
	Piece(ObjectManager* objManajer, int dan, int suji, std::string strPlayer);
	virtual ~Piece();

	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	virtual bool Move();
	void HitTest();

	void SetPieceCentralTile();

	bool GetUpdate3DPos() const { return _bUpdate3DPos; }
	void SetUpdate3DPos(bool bUpdate3DPos) { _bUpdate3DPos = bUpdate3DPos; }

protected:
	VECTOR _oldPos;

	bool _bUpdate3DPos;

private:
	ObjectManager* _objManager;

};

