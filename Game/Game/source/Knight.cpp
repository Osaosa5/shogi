
#include "Knight.h"
#include "ApplicationMain.h"

Knight::Knight(ObjectManager* objManajer, VECTOR pos, PLAYER_TYPE kPlayer) : Koma(objManajer, pos, kPlayer)
{
	// ÉÇÉfÉãì«Ç›çûÇ›
	_handle = RM::MV1LoadModel("res/3D/shogi/keima.mv1");
}

Knight::~Knight()
{
}

bool Knight::Terminate()
{
	return true;
}

bool Knight::Process()
{
	Koma::Process();
	HitTest();
	return true;
}

bool Knight::Render()
{
	Koma::Render();

	return true;
}
