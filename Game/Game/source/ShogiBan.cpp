#include "ShogiBan.h"

ShogiBan::ShogiBan()
{
	// モデルの読み込み
	_modelHandle = MV1LoadModel("res/3D/将棋盤/sho_giban.mv1");
	// 位置情報
	_pos = VGet(0, 0, 0);
	_rot = VGet(0, 0, 0);

}

ShogiBan::~ShogiBan()
{
}

bool ShogiBan::Terminate()
{
	// モデルの削除
	MV1DrawModel(_modelHandle);

	return true;
}

bool ShogiBan::Process()
{
	return true;
}

bool ShogiBan::Render()
{
	// モデルの描画
	MV1DrawModel(_modelHandle);

	return true;
}
