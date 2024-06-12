
#include "GoldGeneral.h"
#include "GoldGeneral.h"

GoldGeneral::GoldGeneral(ObjectManager* objManajer, VECTOR pos, PLAYER_TYPE kPlayer) : Koma(objManajer, pos, kPlayer)
{
	// ���f���ǂݍ���
	_handle = MV1LoadModel("res/3D/shogi/kin.mv1");
}

GoldGeneral::~GoldGeneral()
{
}

bool GoldGeneral::Terminate()
{
	return true;
}

bool GoldGeneral::Process()
{
	Koma::Process();
	HitTest();
	return true;
}

bool GoldGeneral::Render()
{
	// �p�x�ƈʒu���Z�b�g���ĕ`��
	MV1SetRotationXYZ(_handle, _rot);
	MV1SetPosition(_handle, _pos);
	MV1DrawModel(_handle);
	
	return true;
}