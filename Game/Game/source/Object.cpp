
#include "Object.h"

Object::Object()
{
	_name = "";
	_id = 1;

	_handle = -1;
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


void Object::DebugRenderPos()
{
	VECTOR pos = ConvWorldPosToScreenPos(_pos);
	int oldFontSize = GetFontSize();
	SetFontSize(oldFontSize * 2);
	DrawFormatString(pos.x, pos.y, GetColor(255, 0, 0), "%s \nx:%3.2f y:%3.2f z:%3.2f", _name.c_str(), _pos.x, _pos.y, _pos.z);
	SetFontSize(oldFontSize);
}

std::any Object::Get(const std::string& key)
{
	auto it = _mGets.find(key);
	if (it != _mGets.end()) {
		return it->second();
	}
	return std::any();
}
