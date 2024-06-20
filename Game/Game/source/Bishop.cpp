
#include "Bishop.h"
#include "ApplicationMain.h"


Bishop::Bishop(ObjectManager* objManajer, int dan, int suji, PLAYER_TYPE kPlayer)
	: Koma(objManajer, dan, suji, kPlayer)
{
	// ÉÇÉfÉãì«Ç›çûÇ›
	_handle = RM::MV1LoadModel("res/3D/shogi/kaku.mv1");


}

Bishop::~Bishop()
{
}

bool Bishop::Terminate()
{
	return true;
}

bool Bishop::Process()
{
	Koma::Process();
	HitTest();
	return true;
}

bool Bishop::Render()
{
	Koma::Render();

	return true;
}
