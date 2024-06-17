
#include "Fuhyo.h"
#include "ApplicationMain.h"


Fuhyo::Fuhyo(ObjectManager* objManajer, VECTOR pos, int dan, int suji, PLAYER_TYPE kPlayer)
	: Koma(objManajer, pos, dan, suji, kPlayer)
{
	_handle = RM::MV1LoadModel("res/3D/shogi/fuhyo.mv1");
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
	Koma::Render();

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
