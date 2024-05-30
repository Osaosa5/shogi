
#include "Tatami.h"

Tatami::Tatami(VECTOR pos)
{
	// モデルの読み込み
	_handle = MV1LoadModel("res/3D/tatami/ImageToStl.com_772_tatami.mv1");
	// 位置情報
	_pos = pos;
}

Tatami::~Tatami()
{
}

bool Tatami::Terminate()
{
	// モデルの削除
	MV1DeleteModel(_handle);

	return true;
}

bool Tatami::Render()
{
	// モデルの位置情報を設定して描画
	MV1SetPosition(_handle, _pos);
	MV1DrawModel(_handle);

	return true;
}
