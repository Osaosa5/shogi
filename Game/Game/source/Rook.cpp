
#include "Rook.h"

Rook::Rook(ObjectManager* objManajer, int dan, int suji, PLAYER_TYPE kPlayer) 
	: Koma(objManajer, dan, suji, kPlayer)
{
	// モデル読み込み
	_handle = RM::MV1LoadModel("res/3D/shogi/hisha.mv1");
	// コマのタイプを飛車にする
	_komaType = kHisha;
}

Rook::~Rook()
{
}

bool Rook::Terminate()
{
	return true;
}

bool Rook::Process()
{
	Koma::Process();
	HitTest();
	return true;
}

bool Rook::Render()
{
	Koma::Render();

	return true;
}