
#include "King.h"
#include "ApplicationMain.h"

King::King(ObjectManager* objManajer, int dan, int suji, PLAYER_TYPE kPlayer)
	: Piece(objManajer, dan, suji, kPlayer)
{
	// ���f���ǂݍ���
	_handle = (kPlayer == PLAYER_TYPE::kPlayer1) ? RM::MV1LoadModel("res/3D/shogi/oh.mv1") : RM::MV1LoadModel("res/3D/shogi/gyoku.mv1");	
	// �R�}�̃^�C�v�������ɂ���
	_pieceType = kKing;
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
	HitTest();
	return true;
}

bool King::Render()
{
	Piece::Render();

	return true;
}