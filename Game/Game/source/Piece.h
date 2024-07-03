#pragma once

#include "Shogi.h"

#include "ObjectManager.h"
#include "Square.h"

class Piece : public Shogi
{
public:
	Piece(ObjectManager* objManajer, int dan, int suji, PLAYER_TYPE kPlayer);
	virtual ~Piece();

	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	virtual bool Move();
	void HitTest();
	void RegisterPieceToSquare();

	class Square* GetSquarePutPiece(int dan, int suji);
	void SetPieceCentralTile();

	bool GetUpdateBoardPos() const { return _bUpdateBoardPos; }
	void SetUpdateBoardPos(bool bUpdateBoardPos) { _bUpdateBoardPos = bUpdateBoardPos; }
	bool GetUpdate3DPos() const { return _bUpdate3DPos; }
	void SetUpdate3DPos(bool bUpdate3DPos) { _bUpdate3DPos = bUpdate3DPos; }

protected:
	VECTOR _oldPos;
	bool _bIsRegisterPieceToSquare;
	bool _bUpdateBoardPos;
	bool _bUpdate3DPos;

private:
	ObjectManager* _objManager;

};

