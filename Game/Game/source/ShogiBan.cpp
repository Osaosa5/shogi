#include "ShogiBan.h"

ShogiBan::ShogiBan()
{
	// ���f���̓ǂݍ���
	_modelHandle = MV1LoadModel("res/3D/������/sho_giban.mv1");
	// �ʒu���
	_pos = VGet(0, 0, 0);
	_rot = VGet(0, 0, 0);

}

ShogiBan::~ShogiBan()
{
}

bool ShogiBan::Terminate()
{
	// ���f���̍폜
	MV1DrawModel(_modelHandle);

	return true;
}

bool ShogiBan::Process()
{
	return true;
}

bool ShogiBan::Render()
{
	// ���f���̕`��
	MV1DrawModel(_modelHandle);

	return true;
}
