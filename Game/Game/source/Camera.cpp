
#include "Camera.h"
#include "ApplicationMain.h"

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

	_isDebugCamera= false;
	_oldPos = _pos;
	VECTOR distance = VSub(_pos, _direction);
	_radius = VSize(distance);
	_angleSpeed = DX_PI / 180.f;
	_angle = std::atan2(_pos.z - _direction.z, _pos.x - _direction.x);
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
	if(!_isDebugCamera) return false;

	_oldPos = _pos;

	auto app = ApplicationMain::GetInstance();
	int key = app->GetKey();

	if(key & PAD_INPUT_4)	_angle -= _angleSpeed;
	if(key & PAD_INPUT_6)	_angle += _angleSpeed;

	float x = _radius * std::cos(_angle);
	float z = _radius * std::sin(_angle);

	VECTOR newPos = VGet(_direction.x + x, _pos.y, _direction.z + z);
	_pos = newPos;

	// �J�����̈ʒu�ƒ����_��ݒ肷��
	SetCameraPositionAndTarget_UpVecY(_pos, _direction);

	return true;
}

