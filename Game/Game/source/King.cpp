
#include "King.h"
#include "ApplicationMain.h"

King::King(ObjectManager* objManajer, int dan, int suji, PLAYER_TYPE kPlayer)
	: Koma(objManajer, dan, suji, kPlayer)
{
	// モデル読み込み
	_handle = (kPlayer == PLAYER_TYPE::kPlayer1) ? RM::MV1LoadModel("res/3D/shogi/oh.mv1") : RM::MV1LoadModel("res/3D/shogi/gyoku.mv1");	
	// コマのタイプを王将にする
	_komaType = kOsho;
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