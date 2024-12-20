
#include "Bishop.h"
#include "ApplicationMain.h"


Bishop::Bishop(ObjectManager* objManajer, int dan, int suji, std::string strPlayer)
	: Piece(objManajer, dan, suji, strPlayer)
{
	// モデル読み込み
	_handle = RM::MV1LoadModel("res/3D/shogi/kaku.mv1");
	// コマのタイプを角にする
	_pieceType = kBishop;
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
	Piece::Process();
	HitTest();
	return true;
}

bool Bishop::Render()
{
	Piece::Render();

	return true;
}
