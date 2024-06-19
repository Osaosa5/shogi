
#include "Lance.h"
#include "ApplicationMain.h"

Lance::Lance(ObjectManager* objManajer, int dan, int suji, PLAYER_TYPE kPlayer) 
	: Koma(objManajer, dan, suji, kPlayer)
{
	// ÉÇÉfÉãì«Ç›çûÇ›
	_handle = RM::MV1LoadModel("res/3D/shogi/kyousha.mv1");
}

Lance::~Lance()
{
}

bool Lance::Terminate()
{
	return true;
}

bool Lance::Process()
{
	Koma::Process();
	HitTest();
	return true;
}

bool Lance::Render()
{
	Koma::Render();

	return true;
}