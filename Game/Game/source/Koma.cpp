
#include "Koma.h"
#include "appframe.h"

Koma::Koma(ObjectManager* objManajer)
{
	_objManajer = objManajer;
}

Koma::~Koma()
{
}

bool Koma::Terminate()
{
	return true;
}

bool Koma::Process()
{
	VECTOR oldPos = _pos;
	float colSubY = 40.0f;
	_pos.y -= 1.0f;
	// 駒の当たり判定
	MV1_COLL_RESULT_POLY hitPoly;
	auto shogiBan = _objManajer->Get("shogiban");
	auto shogiBanHandle = shogiBan->GetHandle();
	hitPoly = MV1CollCheck_Line(shogiBanHandle, 2,
		VAdd(_pos, VGet(0, colSubY, 0)),
		VAdd(_pos, VGet(0, -999, 0)));
	if(hitPoly.HitFlag)
	{
		// 駒がある場合
		_pos.y = hitPoly.HitPosition.y;
	}
	else
	{
		// 駒がない場合
		_pos = oldPos;
	}

	return true;
}

bool Koma::Render()
{
	return true;
}

bool Koma::Move()
{
	return true;
}
