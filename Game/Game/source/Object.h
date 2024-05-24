#pragma once

#include <string>

class ObjectManager;

class Object
{
public:
	Object();
	virtual ~Object();

	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

private:
	// �A�N�Z�X�������邽�߂�friend�錾���s��
	friend class ObjectManager;
	// �A�N�Z�X���邽�߂̏��
	std::string _name;	// ���O
	int _id;			// ID
};