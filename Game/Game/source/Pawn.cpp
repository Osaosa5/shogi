
#include "Pawn.h"
#include "ApplicationMain.h"


Pawn::Pawn(ObjectManager* objManajer, int dan, int suji, std::string strPlayer)
	: Piece(objManajer, dan, suji, strPlayer)
{
	_handle = RM::MV1LoadModel("res/3D/shogi/fuhyo.mv1");

	// コマのタイプを歩にする
	_kPieceType = PIECE_TYPE::Pawn;

	_vMoveRange = JsonManeger::LoadJsonFile("JSON/board.json")["Pawn"].get<std::vector<int>>();
}

Pawn::~Pawn()
{
}

bool Pawn::Terminate()
{
	MV1DeleteModel(_handle);
	return true;
}

bool Pawn::Process()
{
	Piece::Process();
	
	return true;
}

bool Pawn::Render()
{
	Piece::Render();

	return true;
}

