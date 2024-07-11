#include "ModeDebug.h"

ModeDebug::ModeDebug(ObjectManager* objManager)
{
	_objManager = objManager;
}

bool ModeDebug::Initialize()
{
	return true;
}

bool ModeDebug::Terminate()
{
	return true;
}

bool ModeDebug::Process()
{
	return true;
}

bool ModeDebug::Render()
{
	return true;
}
