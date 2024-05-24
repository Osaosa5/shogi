#include "Light.h"

Light::Light()
{
	_pos = VGet(0, 0, 0);
	_rot = VGet(0.144f, -0.551f, 0.822f);

	// 標準ライトを無効にする
	SetLightEnable(FALSE);
	// グローバルアンビエントライトカラーを設定する
	SetGlobalAmbientLight(GetColorF(0.200f, 0.200f, 0.200f, 0.0f));

	// ライトハンドルを作成する(ディレクショナルライト)
	_handle = CreateDirLightHandle(_rot);
	// ディフューズカラーを設定する
	SetLightDifColorHandle(_handle, GetColorF(1.000f, 1.000f, 1.000f, 1.000f));
	// スペキュラカラーを設定する
	SetLightSpcColorHandle(_handle, GetColorF(0.500f, 0.500f, 0.500f, 0.000f));
	// アンビエントカラーを設定する
	SetLightAmbColorHandle(_handle, GetColorF(0.000f, 0.000f, 0.000f, 0.000f));

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
