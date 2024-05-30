
#include "Koma.h"
#include "appframe.h"

Koma::Koma(ObjectManager* objManajer)
{
	_objManajer = objManajer;
	_oldPos = VGet(0, 0, 0);
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
	_oldPos = _pos;
	return true;
}

bool Koma::Render()
{
	float colSubY = 40.0f;
	// ‹î‚Ì“–‚½‚è”»’è
	MV1_COLL_RESULT_POLY hitPoly;
	auto shogiBan = _objManajer->Get("shogiban");
	auto shogiBanHandle = shogiBan->GetHandle();
	hitPoly = MV1CollCheck_Line(shogiBanHandle, 2,
		VAdd(_pos, VGet(0, colSubY, 0)),
		VAdd(_pos, VGet(0, -999, 0)));
	if (hitPoly.HitFlag) {
		DrawTriangle3D(
			hitPoly.Position[0],
			hitPoly.Position[1],
			hitPoly.Position[2], GetColor(0, 255, 255), TRUE);
	}
	
	return true;
}

bool Koma::Move()
{
	return true;
}

void Koma::HitTest()
{
	float colSubY = 40.0f;
	// ‹î‚Ì“–‚½‚è”»’è
	MV1_COLL_RESULT_POLY hitPoly;
	auto shogiBan = _objManajer->Get("shogiban");
	auto shogiBanHandle = shogiBan->GetHandle();
	hitPoly = MV1CollCheck_Line(shogiBanHandle, 2,
		VAdd(_pos, VGet(0, colSubY, 0)),
		VAdd(_pos, VGet(0, -999, 0)));
	if (hitPoly.HitFlag)
	{
		// ‹î‚ª‚ ‚éê‡
		_pos.y = hitPoly.HitPosition.y;
	}
	else
	{
		// ‹î‚ª‚È‚¢ê‡
		_pos = _oldPos;
	}

}

