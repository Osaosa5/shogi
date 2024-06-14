#include "Camera.h"

Camera::Camera()
{
	_pos = VGet(0, 50, -20);
	_direction = VGet(0, 10, 0);
	_clipNear = 0.1f;
	_clipFar = 2000.0f;
	
	// カメラの手前クリップ距離と奥クリップ距離を設定する
	SetCameraNearFar(_clipNear, _clipFar);
	// カメラの位置と注視点を設定する
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
	// カメラの位置と注視点を設定する
	//SetCameraPositionAndTarget_UpVecY(_pos, _direction);

	return true;
}

