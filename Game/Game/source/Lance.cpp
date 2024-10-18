
#include "Lance.h"
#include "ApplicationMain.h"

Lance::Lance(ObjectManager* objManajer, int dan, int suji, std::string strPlayer)
	: Piece(objManajer, dan, suji, strPlayer)
{
	// モデル読み込み
	_handle = RM::MV1LoadModel("res/3D/shogi/kyousha.mv1");

	// コマのタイプを香車にする
	_kPieceType = PIECE_TYPE::Lance;

	_vMoveRange = JsonManeger::LoadJsonFile("JSON/board.json")["Lance"].get<std::vector<int>>();
}

Lance::~Lance()
{
}

bool Lance::Terminate()
{
	return true;
}

bool Lance::Process()
{
	Piece::Process();
	
	return true;
}

bool Lance::Render()
{
	Piece::Render();

	return true;
}