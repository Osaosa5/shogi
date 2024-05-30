#include "Light.h"

Light::Light()
{
	_pos = VGet(0, -1, 0);

	// �W�����C�g�𖳌��ɂ���
	SetLightEnable(FALSE);
	// ���C�g�n���h�����쐬����(�f�B���N�V���i�����C�g)
	_handle = CreateDirLightHandle(_pos);
}

Light::~Light()
{
}

bool Light::Terminate()
{
	// ���C�g�n���h�����폜����
	DeleteLightHandle(_handle);

	return true;
}
