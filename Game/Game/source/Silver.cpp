
#include "Silver.h"
#include "ApplicationMain.h"

Silver::Silver(ObjectManager* objManajer, int dan, int suji, std::string strPlayer)
	: Piece(objManajer, dan, suji, strPlayer)
{
	// モデル読み込み
	_handle = RM::MV1LoadModel("res/3D/shogi/gin.mv1");

	// コマのタイプを銀にする
	_kPieceType = PIECE_TYPE::Silver;
}

Silver::~Silver()
{
}

bool Silver::Terminate()
{
	return true;
}

bool Silver::Process()
{
	Piece::Process();
	HitTest();
	return true;
}

bool Silver::Render()
{
	Piece::Render();

	return true;
}