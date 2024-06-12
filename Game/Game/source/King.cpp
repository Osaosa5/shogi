
#include "King.h"
#include "ApplicationMain.h"

King::King(ObjectManager* objManajer, VECTOR pos, PLAYER_TYPE kPlayer) : Koma(objManajer, pos, kPlayer)
{
	// ÉÇÉfÉãì«Ç›çûÇ›
	_handle = (kPlayer == PLAYER_TYPE::kPlayer1) ? RM::MV1LoadModel("res/3D/shogi/oh.mv1") : RM::MV1LoadModel("res/3D/shogi/gyoku.mv1");	
}

King::~King()
{
}

bool King::Terminate()
{
	return true;
}

bool King::Process()
{
	Koma::Process();
	HitTest();
	return true;
}

bool King::Render()
{
	Koma::Render();

	return true;
}