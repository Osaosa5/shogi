#pragma once

#include "appframe.h"

#include <string>

class ObjectManager;

class Object
{
public:
	Object();
	virtual ~Object();

	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:
	// オブジェクトの基本情報
	int		_modelHandle;	// モデルハンドル
	VECTOR	_pos;		// 位置
	VECTOR	_rot;		// 回転

private:
	// アクセスを許可するためにfriend宣言を行う
	friend class ObjectManager;
	// アクセスするための情報
	std::string _name;	// 名前
	int _id;			// ID

};