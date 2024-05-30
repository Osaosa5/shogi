
#include "Tatami.h"

Tatami::Tatami(VECTOR pos)
{
	// ���f���̓ǂݍ���
	_handle = MV1LoadModel("res/3D/tatami/ImageToStl.com_772_tatami.mv1");
	// �ʒu���
	_pos = pos;
}

Tatami::~Tatami()
{
}

bool Tatami::Terminate()
{
	// ���f���̍폜
	MV1DeleteModel(_handle);

	return true;
}

bool Tatami::Render()
{
	// ���f���̈ʒu����ݒ肵�ĕ`��
	MV1SetPosition(_handle, _pos);
	MV1DrawModel(_handle);

	return true;
}
