#pragma once

#include "appframe.h"

#include <string>

class ObjectManager;

class Object
{
	typedef ResourceManager RM;
public:
	Object();
	virtual ~Object();

	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	int GetHandle() const { return _handle; }
	VECTOR GetPos() const { return _pos; }
	void SetPos(VECTOR pos) { _pos = pos; }
	VECTOR GetRot() const { return _rot; }

	virtual void DebugRenderPos();

protected:
	// オブジェクトの基本情報
	int		_handle;	// モデルハンドル
	VECTOR	_pos;		// 位置
	VECTOR	_rot;		// 回転

private:
	// アクセスを許可するためにfriend宣言を行う
	friend class ObjectManager;
	// アクセスするための情報
	std::string _name;	// 名前
	int _id;			// ID

};



