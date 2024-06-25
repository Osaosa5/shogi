
#include "SilverGeneral.h"
#include "ApplicationMain.h"

SilverGeneral::SilverGeneral(ObjectManager* objManajer, int dan, int suji, PLAYER_TYPE kPlayer) 
	: Koma(objManajer, dan, suji, kPlayer)
{
	// ���f���ǂݍ���
	_handle = RM::MV1LoadModel("res/3D/shogi/gin.mv1");
	// �R�}�̃^�C�v����ɂ���
	_komaType = kGinsho;
}

SilverGeneral::~SilverGeneral()
{
}

bool SilverGeneral::Terminate()
{
	return true;
}

bool SilverGeneral::Process()
{
	Koma::Process();
	HitTest();
	return true;
}

bool SilverGeneral::Render()
{
	Koma::Render();

	return true;
}