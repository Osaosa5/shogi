
#include "Gold.h"

Gold::Gold(ObjectManager* objManajer, int dan, int suji, std::string strPlayer)
	: Piece(objManajer, dan, suji, strPlayer)
{
	// ���f���ǂݍ���
	_handle = RM::MV1LoadModel("res/3D/shogi/kin.mv1");

	// �R�}�̃^�C�v�����ɂ���
	_kPieceType = PIECE_TYPE::Gold;

	_vMoveRange = JsonManeger::LoadJsonFile("JSON/board.json")["Gold"].get<std::vector<int>>();
}

Gold::~Gold()
{
}

bool Gold::Terminate()
{
	return true;
}

bool Gold::Process()
{
	Piece::Process();
	HitTest();
	return true;
}

bool Gold::Render()
{
	Piece::Render();

	return true;
}