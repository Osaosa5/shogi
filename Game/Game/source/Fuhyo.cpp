
#include "Fuhyo.h"
#include "ApplicationMain.h"

Fuhyo::Fuhyo(ObjectManager* objManajer, VECTOR pos, PLAYER_TYPE kPlayer) : Koma(objManajer, pos, kPlayer)
{
	_handle = MV1LoadModel("res/3D/shogi/fuhyo.mv1");
}

Fuhyo::~Fuhyo()
{
}

bool Fuhyo::Terminate()
{
	MV1DeleteModel(_handle);
	return true;
}

bool Fuhyo::Process()
{
	Koma::Process();
	Move();
	HitTest();
	return true;
}

bool Fuhyo::Render()
{
	//Koma::Render();
	MV1SetRotationXYZ(_handle, _rot);
	MV1SetPosition(_handle, _pos);
	MV1DrawModel(_handle);
	//Object::DebugRenderPos();
	return true;
}

bool Fuhyo::Move()
{
	auto app = ApplicationMain::GetInstance();
	int key = app->GetKey();

	if (key & PAD_INPUT_UP) {_pos.z += 1;}
	if (key & PAD_INPUT_DOWN) {_pos.z -= 1;}
	if (key & PAD_INPUT_LEFT) {_pos.x -= 1;}
	if (key & PAD_INPUT_RIGHT) {_pos.x += 1;}

	return true;
}
