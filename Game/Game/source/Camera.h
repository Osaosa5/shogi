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

private:
	// �����x�N�g��
	VECTOR	_direction;
	// �J�����̎�O�N���b�v�A���N���b�v
	float	_clipNear, _clipFar;
};

