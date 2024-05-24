#include "Camera.h"

Camera::Camera()
{
	_pos = VGet(0, 100, -500);
	_direction = VGet(0, 0, 0);
	_clipNear = 0.1f;
	_clipFar = 1000.0f;
}

Camera::~Camera()
{
}

bool Camera::Initialize()
{
	// �J�����̎�O�N���b�v�����Ɖ��N���b�v������ݒ肷��
	SetCameraNearFar(_clipNear, _clipFar);
	// �J�����̈ʒu�ƒ����_��ݒ肷��
	SetCameraPositionAndTarget_UpVecY(_pos, _direction);

	return true;
}

bool Camera::Terminate()
{
	return true;
}

bool Camera::Process()
{
	// �J�����̈ʒu�ƒ����_��ݒ肷��
	SetCameraPositionAndTarget_UpVecY(_pos, _direction);

	return true;
}

bool Camera::Render()
{
	return true;
}
