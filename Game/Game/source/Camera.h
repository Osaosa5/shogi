#pragma once

#include "Object.h"

#include "appframe.h"

class Camera : public Object
{
public:
	Camera();
	~Camera();

	bool Terminate() override;
	bool Process() override;

	bool GetIsDebugCamera()						{ return _isDebugCamera; }
	void SetIsDebugCamera(bool isDebugCamera)	{ _isDebugCamera = isDebugCamera; }

private:
	// �����x�N�g��
	VECTOR	_direction;
	// �J�����̎�O�N���b�v�A���N���b�v
	float	_clipNear, _clipFar;

	// �f�o�b�O���[�h���̕ϐ�
	bool _isDebugCamera;	// �f�o�b�O���ǂ���
	VECTOR _oldPos;			// 1�t���[���O�̃J�����̈ʒu
	float _radius;			// �J�����̔��a
	float _angleSpeed;		// �J�����̈ړ����x
	float _angle;			// �J�����̊p�x
};

