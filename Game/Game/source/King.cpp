
#include "King.h"
#include "ApplicationMain.h"

King::King(ObjectManager* objManajer, int dan, int suji, std::string strPlayer)
	: Piece(objManajer, dan, suji, strPlayer)
{
	// ���f���ǂݍ���
	_handle = (strPlayer == "player1") ? RM::MV1LoadModel("res/3D/shogi/oh.mv1") : RM::MV1LoadModel("res/3D/shogi/gyoku.mv1");

	// �R�}�̃^�C�v�������ɂ���
	_kPieceType = PIECE_TYPE::King;

	_vMoveRange = JsonManeger::LoadJsonFile("JSON/board.json")["King"].get<std::vector<int>>();
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
	Piece::Process();
	
	return true;
}

bool King::Render()
{
	Piece::Render();

	return true;
}