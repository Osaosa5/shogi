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
	// カメラの手前クリップ距離と奥クリップ距離を設定する
	SetCameraNearFar(_clipNear, _clipFar);
	// カメラの位置と注視点を設定する
	SetCameraPositionAndTarget_UpVecY(_pos, _direction);

	return true;
}

bool Camera::Terminate()
{
	return true;
}

bool Camera::Process()
{
	// カメラの位置と注視点を設定する
	SetCameraPositionAndTarget_UpVecY(_pos, _direction);

	return true;
}

bool Camera::Render()
{
	return true;
}
