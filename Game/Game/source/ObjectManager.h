#pragma once

#include "Object.h"

#include <list>

class ObjectManager
{
	typedef std::vector<Object*> lstObject;

public:
	ObjectManager();
	virtual ~ObjectManager();
	static ObjectManager *_lpInstance;
	static ObjectManager *GetInstance() { return (ObjectManager*)_lpInstance; }

	// obj�̒ǉ��E�폜
	int Add(Object *pObject, const char *name);	// obj�̒ǉ�
	int Del(Object *pObject);					// obj�̍폜
	void Clear();								// �S�폜

	// obj�̎擾
	Object *Get(int id);			// id�Ŏ擾
	Object *Get(const char *name);	// ���O�Ŏ擾

	// id�̎擾
	int GetId(Object* pObject);		// obj����id���擾
	int GetId(const char *name);	// ���O����id���擾

	// ���O�̎擾
	const char *GetName(Object* pObject);	// obj���疼�O���擾
	const char *GetName(int id);			// id���疼�O���擾

	// ���C���̏���
	int ProcessInit();	// �v���Z�X���񂷂��߂̏�����
	int Process();		// �v���Z�X����

	// �`��
	int Render();		// �`��

private:
	int	 Release(Object *pObject);			// �폜��delete
	bool IsDelRegister(Object *pObject);	// �폜�o�^����Ă��邩
	bool IsAdd(Object *pObject);			// �ǉ�����Ă��邩)

	lstObject	_vObject;		// �I�u�W�F�N�g���X�g
	int			_idCnt;			// id�J�E���^
	lstObject	_vObjctAdd;		// �ǉ����X�g
	lstObject	_vObjctDel;		// �폜���X�g
};

