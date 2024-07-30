
#include "Lance.h"
#include "ApplicationMain.h"

Lance::Lance(ObjectManager* objManajer, int dan, int suji, std::string strPlayer)
	: Piece(objManajer, dan, suji, strPlayer)
{
	// ���f���ǂݍ���
	_handle = RM::MV1LoadModel("res/3D/shogi/kyousha.mv1");

	// �R�}�̃^�C�v�����Ԃɂ���
	_kPieceType = PIECE_TYPE::Lance;
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
	HitTest();
	return true;
}

bool Lance::Render()
{
	Piece::Render();

	return true;
}