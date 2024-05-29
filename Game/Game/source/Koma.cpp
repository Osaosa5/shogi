
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
	// ‹î‚Ì“–‚½‚è”»’è
	MV1_COLL_RESULT_POLY hitPoly;
	auto shogiBan = _objManajer->Get("shogiban");
	auto shogiBanHandle = shogiBan->GetHandle();
	hitPoly = MV1CollCheck_Line(shogiBanHandle, 2,
		VAdd(_pos, VGet(0, colSubY, 0)),
		VAdd(_pos, VGet(0, -999, 0)));
	if(hitPoly.HitFlag)
	{
		// ‹î‚ª‚ ‚éê‡
		_pos.y = hitPoly.HitPosition.y;
	}
	else
	{
		// ‹î‚ª‚È‚¢ê‡
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
