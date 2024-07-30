#pragma once

#include "appframe.h"
#include "ObjectManager.h"

class WidgetManager;

class Widget
{
	typedef ResourceManager RM;
public:
	Widget(ObjectManager* ptrObjManager);
	virtual ~Widget();

	virtual bool Initialize()	= 0;
	virtual bool Terminate()	= 0;
	virtual bool Process()		= 0;
	virtual bool Render()		= 0;

	// セッター・ゲッター
	VECTOR		GetPos() const		{ return _pos; }
	void		SetPos(VECTOR pos)	{ _pos = pos; }

	bool		GetIsView() const		{ return _isView; }
	void		SetIsView(bool isView)	{ _isView = isView; }

	const char* GetName() const { return _name.c_str(); }
	int			GetId() const	{ return _id; }


protected:
	ObjectManager*	_ptrObjManager;	// オブジェクト管理
	VECTOR			_pos;			// 位置
	bool			_isView;		// 表示フラグ

private:
	friend class WidgetManager;
	std::string _name;	// 名前
	int			_id;	// ID
};

