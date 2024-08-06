
#include "Knight.h"
#include "ApplicationMain.h"

Knight::Knight(ObjectManager* objManajer, int dan, int suji, std::string strPlayer)
	: Piece(objManajer, dan, suji, strPlayer)
{
	// モデル読み込み
	_handle = RM::MV1LoadModel("res/3D/shogi/keima.mv1");

	// コマのタイプを桂馬にする
	_kPieceType = PIECE_TYPE::Knight;

	_vMoveRange = JsonManeger::LoadJsonFile("JSON/board.json")["Knight"].get<std::vector<int>>();
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
