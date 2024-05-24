
#include "Object.h"

Object::Object()
{
	_name = "";
	_id = 1;
}

Object::~Object()
{
}

bool Object::Initialize()
{
	return true;
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
