
#include "Knight.h"
#include "ApplicationMain.h"

Knight::Knight(ObjectManager* objManajer, int dan, int suji, PLAYER_TYPE kPlayer) 
	: Koma(objManajer, dan, suji, kPlayer)
{
	// ���f���ǂݍ���
	_handle = RM::MV1LoadModel("res/3D/shogi/keima.mv1");
	// �R�}�̃^�C�v���j�n�ɂ���
	_komaType = kKeima;
}

Knight::~Knight()
{
}

bool Knight::Terminate()
{
	return true;
}

bool Knight::Process()
{
	Koma::Process();
	HitTest();
	return true;
}

bool Knight::Render()
{
	Koma::Render();

	return true;
}
