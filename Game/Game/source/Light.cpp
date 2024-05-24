#include "Light.h"

Light::Light()
{
	_pos = VGet(0, 0, 0);
	_rot = VGet(0.144f, -0.551f, 0.822f);

	SetLightEnable(FALSE);
	SetGlobalAmbientLight(GetColorF(0.200f, 0.200f, 0.200f, 0.0f));

	_modelHandle = CreateDirLightHandle(_rot);
	SetLightDifColorHandle(_modelHandle, GetColorF(1.000f, 1.000f, 1.000f, 1.000f));
	SetLightSpcColorHandle(_modelHandle, GetColorF(0.500f, 0.500f, 0.500f, 0.000f));
	SetLightAmbColorHandle(_modelHandle, GetColorF(0.000f, 0.000f, 0.000f, 0.000f));

}

Light::~Light()
{
}

bool Light::Terminate()
{
	DeleteLightHandle(_modelHandle);
	return true;
}

bool Light::Process()
{
	return true;
}

bool Light::Render()
{
	return true;
}
