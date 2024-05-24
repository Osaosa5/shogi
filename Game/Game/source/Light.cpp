#include "Light.h"

Light::Light()
{
	_pos = VGet(0, 0, 0);
	_rot = VGet(0.144f, -0.551f, 0.822f);

	// �W�����C�g�𖳌��ɂ���
	SetLightEnable(FALSE);
	// �O���[�o���A���r�G���g���C�g�J���[��ݒ肷��
	SetGlobalAmbientLight(GetColorF(0.200f, 0.200f, 0.200f, 0.0f));

	// ���C�g�n���h�����쐬����(�f�B���N�V���i�����C�g)
	_handle = CreateDirLightHandle(_rot);
	// �f�B�t���[�Y�J���[��ݒ肷��
	SetLightDifColorHandle(_handle, GetColorF(1.000f, 1.000f, 1.000f, 1.000f));
	// �X�y�L�����J���[��ݒ肷��
	SetLightSpcColorHandle(_handle, GetColorF(0.500f, 0.500f, 0.500f, 0.000f));
	// �A���r�G���g�J���[��ݒ肷��
	SetLightAmbColorHandle(_handle, GetColorF(0.000f, 0.000f, 0.000f, 0.000f));

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
