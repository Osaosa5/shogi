
#include "GoldGeneral.h"
#include "GoldGeneral.h"

GoldGeneral::GoldGeneral(ObjectManager* objManajer, int dan, int suji, PLAYER_TYPE kPlayer)
	: Koma(objManajer, dan, suji, kPlayer)
{
	// モデル読み込み
	_handle = RM::MV1LoadModel("res/3D/shogi/kin.mv1");
	// コマのタイプを金にする
	_komaType = kKinsho;
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