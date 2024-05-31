#include "Shogi.h"

Shogi::Shogi()
{
	_suji = 0;
	_dan = 0;
	_elementNum = _suji * DAN_MAX + _dan;
	_areaType = AREA_TYPE::kNone;
	_komaType = KOMA_TYPE::kNoneKoma;
	_playerType = PLAYER_TYPE::kNonePlayer;
}

Shogi::~Shogi()
{
}

bool Shogi::Terminate()
{
	return true;
}

bool Shogi::Process()
{
	return true;
}

bool Shogi::Render()
{
	return true;
}
