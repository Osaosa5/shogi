
#include "Pawn.h"
#include "ApplicationMain.h"


Pawn::Pawn(ObjectManager* objManajer, int dan, int suji, PLAYER_TYPE kPlayer)
	: Piece(objManajer, dan, suji, kPlayer)
{
	_handle = RM::MV1LoadModel("res/3D/shogi/fuhyo.mv1");
	// コマのタイプを歩にする
	_pieceType = kPawn;
}

Pawn::~Pawn()
{
}

bool Pawn::Terminate()
{
	MV1DeleteModel(_handle);
	return true;
}

bool Pawn::Process()
{
	Piece::Process();
	//Move();
	HitTest();
	return true;
}

bool Pawn::Render()
{
	Piece::Render();

	return true;
}

bool Pawn::Move()
{
	auto app = ApplicationMain::GetInstance();
	int key = app->GetKey();

	if (key & PAD_INPUT_UP) {_pos.z += 1;}
	if (key & PAD_INPUT_DOWN) {_pos.z -= 1;}
	if (key & PAD_INPUT_LEFT) {_pos.x -= 1;}
	if (key & PAD_INPUT_RIGHT) {_pos.x += 1;}

	return true;
}
