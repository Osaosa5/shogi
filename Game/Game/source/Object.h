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
	// �I�u�W�F�N�g�̊�{���
	int		_modelHandle;	// ���f���n���h��
	VECTOR	_pos;		// �ʒu
	VECTOR	_rot;		// ��]

private:
	// �A�N�Z�X�������邽�߂�friend�錾���s��
	friend class ObjectManager;
	// �A�N�Z�X���邽�߂̏��
	std::string _name;	// ���O
	int _id;			// ID

};