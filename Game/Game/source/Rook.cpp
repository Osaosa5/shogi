
#include "Rook.h"

Rook::Rook(ObjectManager* objManajer, int dan, int suji, std::string strPlayer)
	: Piece(objManajer, dan, suji, strPlayer)
{
	// ���f���ǂݍ���
	_handle = RM::MV1LoadModel("res/3D/shogi/hisha.mv1");

	// �R�}�̃^�C�v���Ԃɂ���
	_kPieceType = PIECE_TYPE::Rook;
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
	HitTest();
	return true;
}

bool Rook::Render()
{
	Piece::Render();

	return true;
}