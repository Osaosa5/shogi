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
	// 方向ベクトル
	VECTOR	_direction;
	// カメラの手前クリップ、奥クリップ
	float	_clipNear, _clipFar;
};

