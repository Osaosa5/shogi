#pragma once

#include "appframe.h"
#include "ObjectManager.h"

class WidgetManager;

class Widget
{
	typedef ResourceManager RM;
public:
	Widget(ObjectManager* ptrObjManager);
	virtual ~Widget() = 0;

	virtual bool Initialize()	= 0;
	virtual bool Terminate()	= 0;
	virtual bool Process()		= 0;
	virtual bool Render()		= 0;

	// �Z�b�^�[�E�Q�b�^�[
	VECTOR GetPos() const { return _pos; }
	void SetPos(VECTOR pos) { _pos = pos; }
	const char* GetName() const { return _name.c_str(); }
	int GetId() const { return _id; }


protected:
	ObjectManager*	_ptrObjManager;	// �I�u�W�F�N�g�Ǘ�
	VECTOR			_pos;			// �ʒu

private:
	friend class WidgetManager;
	std::string _name;	// ���O
	int			_id;	// ID
};
