
#include "Knight.h"
#include "ApplicationMain.h"

Knight::Knight(ObjectManager* objManajer, int dan, int suji, PLAYER_TYPE kPlayer) 
	: Piece(objManajer, dan, suji, kPlayer)
{
	// モデル読み込み
	_handle = RM::MV1LoadModel("res/3D/shogi/keima.mv1");
	// コマのタイプを桂馬にする
	_pieceType = kKnight;
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
	Piece::Process();
	HitTest();
	return true;
}

bool Knight::Render()
{
	Piece::Render();

	return true;
}
