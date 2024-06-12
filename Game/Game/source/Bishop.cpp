
#include "Bishop.h"
#include "ApplicationMain.h"

Bishop::Bishop(ObjectManager* objManajer, VECTOR pos, PLAYER_TYPE kPlayer) : Koma(objManajer, pos, kPlayer)
{
	// ���f���ǂݍ���
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
