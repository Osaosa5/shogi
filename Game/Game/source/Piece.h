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

	enum class OWNER_TYPE 
	{
		kBoard,
		kPieceStand
	};

	virtual bool Move();
	void HitTest();

	void SetPieceCentralTile();
	void UpdateDirectionForPlayer(PLAYER_TYPE playerType);

	bool GetUpdate3DPos() const				{ return _bUpdate3DPos; }
	void SetUpdate3DPos(bool bUpdate3DPos)	{ _bUpdate3DPos = bUpdate3DPos; }

	OWNER_TYPE	GetOwnerType() const				{ return _ownerType; }
	void		SetOwnerType(OWNER_TYPE ownerType)	{ _ownerType = ownerType; }

protected:
	VECTOR _oldPos;

	bool _bUpdate3DPos;

	OWNER_TYPE _ownerType;

private:
	ObjectManager* _objManager;

};

