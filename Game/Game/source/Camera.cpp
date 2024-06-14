#include "Camera.h"

Camera::Camera()
{
	_pos = VGet(0, 50, -20);
	_direction = VGet(0, 10, 0);
	_clipNear = 0.1f;
	_clipFar = 2000.0f;
	
	// �J�����̎�O�N���b�v�����Ɖ��N���b�v������ݒ肷��
	SetCameraNearFar(_clipNear, _clipFar);
	// �J�����̈ʒu�ƒ����_��ݒ肷��
	SetCameraPositionAndTarget_UpVecY(_pos, _direction);

}

Camera::~Camera()
{
}

bool Camera::Terminate()
{
	return true;
}

bool Camera::Process()
{
	// �J�����̈ʒu�ƒ����_��ݒ肷��
	//SetCameraPositionAndTarget_UpVecY(_pos, _direction);

	return true;
}

