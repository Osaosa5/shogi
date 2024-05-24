#pragma once

#include "Object.h"
#include "appframe.h"

class Model : public Object
{
public:
	Model();
	virtual ~Model();

	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:
	// 基本情報
	int		_modelHandle;	// モデルハンドル
	VECTOR	_pos;			// 位置
	VECTOR	_rot;			// 回転
};

