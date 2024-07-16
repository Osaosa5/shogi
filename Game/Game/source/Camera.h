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
	// 方向ベクトル
	VECTOR	_direction;
	// カメラの手前クリップ、奥クリップ
	float	_clipNear, _clipFar;

	// デバッグモード時の変数
	bool _isDebugCamera;	// デバッグかどうか
	VECTOR _oldPos;			// 1フレーム前のカメラの位置
	float _radius;			// カメラの半径
	float _angleSpeed;		// カメラの移動速度
	float _angle;			// カメラの角度
};

