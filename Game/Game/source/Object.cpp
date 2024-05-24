
#include "Object.h"

Object::Object()
{
	_name = "";
	_id = 1;

	_modelHandle = -1;
	_pos = VGet(0, 0, 0);
	_rot = VGet(0, 0, 0);
}

Object::~Object()
{
}

bool Object::Terminate()
{
	return true;
}

bool Object::Process()
{
	return true;
}

bool Object::Render()
{
	return true;
}
