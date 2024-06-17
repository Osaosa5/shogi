
#include "SilverGeneral.h"
#include "ApplicationMain.h"

SilverGeneral::SilverGeneral(ObjectManager* objManajer, VECTOR pos, int dan, int suji, PLAYER_TYPE kPlayer) 
	: Koma(objManajer, pos, dan, suji, kPlayer)
{
	// ƒ‚ƒfƒ‹“Ç‚İ‚İ
	_handle = RM::MV1LoadModel("res/3D/shogi/gin.mv1");
}

SilverGeneral::~SilverGeneral()
{
}

bool SilverGeneral::Terminate()
{
	return true;
}

bool SilverGeneral::Process()
{
	Koma::Process();
	HitTest();
	return true;
}

bool SilverGeneral::Render()
{
	Koma::Render();

	return true;
}