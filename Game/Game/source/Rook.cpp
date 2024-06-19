
#include "Rook.h"

Rook::Rook(ObjectManager* objManajer, int dan, int suji, PLAYER_TYPE kPlayer) 
	: Koma(objManajer, dan, suji, kPlayer)
{
	// ÉÇÉfÉãì«Ç›çûÇ›
	_handle = RM::MV1LoadModel("res/3D/shogi/hisha.mv1");
}

Rook::~Rook()
{
}

bool Rook::Terminate()
{
	return true;
}

bool Rook::Process()
{
	Koma::Process();
	HitTest();
	return true;
}

bool Rook::Render()
{
	Koma::Render();

	return true;
}