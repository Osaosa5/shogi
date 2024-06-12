
#include "SilverGeneral.h"
#include "ApplicationMain.h"

SilverGeneral::SilverGeneral(ObjectManager* objManajer, VECTOR pos, PLAYER_TYPE kPlayer) : Koma(objManajer, pos, kPlayer)
{
	// モデル読み込み
	_handle = MV1LoadModel("res/3D/shogi/gin.mv1");
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
	// 角度と位置をセットして描画
	MV1SetRotationXYZ(_handle, _rot);
	MV1SetPosition(_handle, _pos);
	MV1DrawModel(_handle);
	
	return true;
}