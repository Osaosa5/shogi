
#include "GoldGeneral.h"
#include "GoldGeneral.h"

GoldGeneral::GoldGeneral(ObjectManager* objManajer, VECTOR pos, PLAYER_TYPE kPlayer) : Koma(objManajer, pos, kPlayer)
{
	// ƒ‚ƒfƒ‹“Ç‚İ‚İ
	_handle = RM::MV1LoadModel("res/3D/shogi/kin.mv1");
}

GoldGeneral::~GoldGeneral()
{
}

bool GoldGeneral::Terminate()
{
	return true;
}

bool GoldGeneral::Process()
{
	Koma::Process();
	HitTest();
	return true;
}

bool GoldGeneral::Render()
{
	Koma::Render();

	return true;
}