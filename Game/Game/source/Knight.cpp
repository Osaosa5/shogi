
#include "Knight.h"
#include "ApplicationMain.h"

Knight::Knight(ObjectManager* objManajer, int dan, int suji, PLAYER_TYPE kPlayer) 
	: Koma(objManajer, dan, suji, kPlayer)
{
	// ƒ‚ƒfƒ‹“Ç‚İ‚İ
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
