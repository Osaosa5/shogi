
#include "Model.h"

Model::Model()
{
	_modelHandle = 0;
	_pos = VGet(0, 0, 0);
	_rot = VGet(0, 0, 0);
}

Model::~Model()
{
}

bool Model::Initialize()
{
	return true;
}

bool Model::Terminate()
{
	return true;
}

bool Model::Process()
{
	return true;
}

bool Model::Render()
{
	return true;
}
