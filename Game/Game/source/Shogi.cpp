
#include "Shogi.h"

Shogi::Shogi()
{
	_suji = 0;
	_dan = 0;
	_tile = _suji * DAN_MAX + _dan;

	AddGet<>("Dan", [&]() -> int {return _dan; });
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
