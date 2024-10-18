
#include "Rook.h"

Rook::Rook(ObjectManager* objManajer, int dan, int suji, std::string strPlayer)
	: Piece(objManajer, dan, suji, strPlayer)
{
	// モデル読み込み
	_handle = RM::MV1LoadModel("res/3D/shogi/hisha.mv1");

	// コマのタイプを飛車にする
	_kPieceType = PIECE_TYPE::Rook;

	_vMoveRange = JsonManeger::LoadJsonFile("JSON/board.json")["Rook"].get<std::vector<int>>();
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
	Piece::Process();
	
	return true;
}

bool Rook::Render()
{
	Piece::Render();

	return true;
}