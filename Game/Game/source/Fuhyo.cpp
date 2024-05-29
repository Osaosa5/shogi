
#include "Fuhyo.h"
#include "ApplicationMain.h"

Fuhyo::Fuhyo(ObjectManager* objManajer) : Koma(objManajer)
{
	_handle = MV1LoadModel("res/3D/«Šû‹î•à•º.mv1");
	// ˆÊ’uî•ñ
	_pos = VGet(0, 30, 0);
	_rot = VGet(0, 0, 0);
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
	HitTestProcess();
	return true;
}

bool Fuhyo::Render()
{

	_rot.x = DEG2RAD(90);
	MV1SetRotationXYZ(_handle, _rot);
	MV1SetPosition(_handle, _pos);
	MV1DrawModel(_handle);

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
