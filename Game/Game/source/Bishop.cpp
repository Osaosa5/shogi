
#include "Bishop.h"
#include "ApplicationMain.h"


Bishop::Bishop(ObjectManager* objManajer, int dan, int suji, PLAYER_TYPE kPlayer)
	: Piece(objManajer, dan, suji, kPlayer)
{
	// ���f���ǂݍ���
	_handle = RM::MV1LoadModel("res/3D/shogi/kaku.mv1");
	// �R�}�̃^�C�v���p�ɂ���
	_pieceType = kBishop;
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
