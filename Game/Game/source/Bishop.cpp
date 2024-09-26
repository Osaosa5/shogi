
#include "Bishop.h"
#include "ApplicationMain.h"


Bishop::Bishop(ObjectManager* objManajer, int dan, int suji, std::string strPlayer)
	: Piece(objManajer, dan, suji, strPlayer)
{
	// ���f���ǂݍ���
	_handle = RM::MV1LoadModel("res/3D/shogi/kaku.mv1");

	// �R�}�̃^�C�v���p�ɂ���
	_kPieceType = PIECE_TYPE::Bishop;

	_vMoveRange = JsonManeger::LoadJsonFile("JSON/board.json")["Bishop"].get<std::vector<int>>();
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