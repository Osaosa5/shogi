#include "Light.h"

Light::Light()
{
	_pos = VGet(0, -1, 0);

	// 標準ライトを無効にする
	SetLightEnable(FALSE);
	// ライトハンドルを作成する(ディレクショナルライト)
	_handle = CreateDirLightHandle(_pos);
}

Light::~Light()
{
}

bool Light::Terminate()
{
	// ライトハンドルを削除する
	DeleteLightHandle(_handle);

	return true;
}
