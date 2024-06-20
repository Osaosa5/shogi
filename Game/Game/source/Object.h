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

	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	int GetHandle() const { return _handle; }
	VECTOR GetPos() const { return _pos; }
	void SetPos(VECTOR pos) { _pos = pos; }
	VECTOR GetRot() const { return _rot; }

	virtual void DebugRenderPos();

protected:
	// �I�u�W�F�N�g�̊�{���
	int		_handle;	// ���f���n���h��
	VECTOR	_pos;		// �ʒu
	VECTOR	_rot;		// ��]

	// �Q�b�^�[�ƃZ�b�^�[���Ăяo�����߂̃R���e�i
	std::map<std::string, std::function<std::any>> _mGets;
	
	
public:
	template<typename Func>
	inline void AddGet(const std::string& key, Func func)
	{
		_mGets[key] = [func]() -> std::any {
			return std::any(func());
		};
	}
	std::any Get(const std::string& key);


private:
	// �A�N�Z�X�������邽�߂�friend�錾���s��
	friend class ObjectManager;
	// �A�N�Z�X���邽�߂̏��
	std::string _name;	// ���O
	int _id;			// ID

};



