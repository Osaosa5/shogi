#include "ObjectManager.h"
#include "Object.h"

/*
	@brief �R���X�g���N�^
*/
ObjectManager::ObjectManager()
{
	_idCnt = 1;
}

/*
	@brief �f�X�g���N�^
*/
ObjectManager::~ObjectManager()
{
	Clear();
}

/*
	@brief �I�u�W�F�N�g�̒ǉ�
	@param pObject�F�ǉ�����I�u�W�F�N�g
	@param name�F�I�u�W�F�N�g�̓o�^��
	@return �ǉ������I�u�W�F�N�g��ID
*/
int ObjectManager::Add(Object* pObject, const char* name)
{
	// �ǉ����X�g�ɓo�^
	_vObjctAdd.push_back(pObject);
	// ID��ݒ�
	pObject->_id = _idCnt;
	// ID���C���N�������g
	_idCnt++;
	// ���O��ݒ�
	pObject->_name = name;
	// id��Ԃ�
	return pObject->_id;
}

/*
	@brief �I�u�W�F�N�g�̍폜
	@param pObject�F�폜����I�u�W�F�N�g
	@return 0
*/
int ObjectManager::Del(Object* pObject)
{
	// �폜���X�g�ɓo�^
	_vObjctDel.push_back(pObject);
	return 0;
}

/*
	@brief �I�u�W�F�N�g�̉��
	@param pObject�F�������I�u�W�F�N�g
	@return 1
*/
int ObjectManager::Release(Object* pObject)
{
	lstObject::iterator ite = _vObject.begin();
	for(; ite != _vObject.end();)
	{
		if((*ite) == pObject)
		{
			(*ite)->Terminate();
			delete (*ite);
			ite = _vObject.erase(ite);
		}
		else  ++ite; 
	}
	return 1;
}

/*
	@brief �I�u�W�F�N�g�̑S�폜
*/
void ObjectManager::Clear()
{
	// obj���X�g�̖������擾
	lstObject::reverse_iterator ite = _vObject.rbegin();
	// obj���X�g�̐擪�܂Ń��[�v
	for(; ite != _vObject.rend(); ++ite)
	{
		// �I�u�W�F�N�g�̏I������
		(*ite)->Terminate();
		// �I�u�W�F�N�g�̍폜
		delete (*ite);
	}
	// �ǉ��I�u�W�F�N�g�̐擪���擾
	lstObject::iterator iteAdd = _vObjctAdd.begin();
	// �ǉ��I�u�W�F�N�g�̖����܂Ń��[�v
	for(; iteAdd != _vObjctAdd.end(); ++iteAdd)
	{
		// �I�u�W�F�N�g�̏I������
		(*iteAdd)->Terminate();
		// �I�u�W�F�N�g�̍폜
		delete (*iteAdd);
	}
	// ���X�g�̃N���A
	_vObject.clear();
	_vObjctAdd.clear();
	_vObjctDel.clear();
}

/*
	@brief �폜�\��̊m�F
*/
bool ObjectManager::IsDelRegister(Object* pObject)
{
	// �폜���X�g�ɓo�^����Ă��邩
	if (_vObjctDel.size() > 0) {
		// �폜���X�g�̐擪���擾
		lstObject::iterator ite = _vObjctDel.begin();
		// �폜���X�g�̖����܂Ń��[�v
		for (; ite != _vObjctDel.end(); ++ite) {
			// �폜���X�g�ɓo�^����Ă��邩
			if ((*ite) == pObject) return true;
		}
	}
	// �o�^����Ă��Ȃ�
	return false;
}

/*
	@brief �I�u�W�F�N�g�̓o�^�m�F
	@param pObject�F�o�^�m�F����I�u�W�F�N�g
	@return true�F�o�^����Ă���
	@return false�F�o�^����Ă��Ȃ�
*/
bool ObjectManager::IsAdd(Object* pObject)
{
	// obj���X�g�̐擪���擾
	lstObject::iterator ite = _vObject.begin();
	// obj���X�g�̖����܂Ń��[�v
	for(; ite != _vObject.end(); ++ite)
	{
		// �o�^����Ă�����true��Ԃ�
		if(!IsDelRegister((*ite)) && (*ite) == pObject) return true;
	}

	// �ǉ����X�g�̐擪���擾
	ite = _vObjctAdd.begin();
	// �ǉ����X�g�̖����܂Ń��[�v
	for (; ite != _vObjctAdd.end(); ++ite)
	{
		// �o�^����Ă�����true��Ԃ�
		if(!IsDelRegister((*ite)) && (*ite) == pObject) return true;
	}
	// �o�^����Ă��Ȃ�
	return false;
}

/*
	@brief �I�u�W�F�N�gID���猟��
	@param id�F��������I�u�W�F�N�gID
	@return ���������I�u�W�F�N�g
	@return NULL�F������Ȃ�����
*/
Object *ObjectManager::Get(int id)
{
	// obj���X�g�̐擪���擾
	lstObject::iterator ite = _vObject.begin();
	// obj���X�g�̖����܂Ń��[�v
	for (; ite != _vObject.end(); ++ite)
	{
		// id����v�����炻�̃I�u�W�F�N�g��Ԃ�
		if(!IsDelRegister((*ite)) && (*ite)->_id == id) return (*ite);
	}

	// �ǉ����X�g�̐擪���擾
	ite = _vObjctAdd.begin();
	// �ǉ����X�g�̖����܂Ń��[�v
	for (; ite != _vObjctAdd.end(); ++ite)
	{
		// id����v�����炻�̃I�u�W�F�N�g��Ԃ�
		if(!IsDelRegister((*ite)) && (*ite)->_id == id) return (*ite);
	}
	// ������Ȃ�����
	return NULL;
}

/*
	@brief �I�u�W�F�N�g�����猟��
	@param name�F��������I�u�W�F�N�g��
	@return ���������I�u�W�F�N�g
	@return NULL�F������Ȃ�����
*/
Object *ObjectManager::Get(const char* name)
{
	// obj���X�g�̐擪���擾
	lstObject::iterator ite = _vObject.begin();
	// obj���X�g�̖����܂Ń��[�v
	for (; ite != _vObject.end(); ++ite)
	{
		// ���O����v�����炻�̃I�u�W�F�N�g��Ԃ�
		if(!IsDelRegister((*ite)) && (*ite)->_name == name) return (*ite);
	}

	// �ǉ����X�g�̐擪���擾
	ite = _vObjctAdd.begin();
	// �ǉ����X�g�̖����܂Ń��[�v
	for (; ite != _vObjctAdd.end(); ++ite)
	{
		// ���O����v�����炻�̃I�u�W�F�N�g��Ԃ�
		if(!IsDelRegister((*ite)) && (*ite)->_name == name) return (*ite);
	}
	// ������Ȃ�����
	return NULL;
}

/*
	@brief �I�u�W�F�N�gID�̎擾
	@param pObject�FID���擾����I�u�W�F�N�g
	@return ID�F�I�u�W�F�N�gID
	@return 0�F������Ȃ�����
*/
int ObjectManager::GetId(Object* pObject)
{
	// �o�^����Ă��邩	ID��Ԃ�
	if (IsAdd(pObject)) return pObject->_id;
	// �o�^����Ă��Ȃ�	
	return 0;
}

/*
	@brief �I�u�W�F�N�gID�̎擾
	@param name�FID���擾����I�u�W�F�N�g��
	@return ID�F�I�u�W�F�N�gID
	@return 0�F������Ȃ�����
*/
int ObjectManager::GetId(const char* name)
{
	// ID���擾
	return GetId(Get(name));
}

/*
	@brief �I�u�W�F�N�g���̎擾
	@param pObject�F���O���擾����I�u�W�F�N�g
	@return ���O�F�I�u�W�F�N�g��
	@return NULL�F������Ȃ�����
*/
const char *ObjectManager::GetName(Object* pObject)
{
	// �o�^����Ă��邩
	if(IsAdd(pObject)) return pObject->_name.c_str();
	// �o�^����Ă��Ȃ�
	return NULL;
}

/*
	@brief �I�u�W�F�N�g���̎擾
	@param id�F���O���擾����I�u�W�F�N�gID
	@return ���O�F�I�u�W�F�N�g��
	@return NULL�F������Ȃ�����
*/
const char *ObjectManager::GetName(int id)
{
	// ���O���擾
	return GetName(Get(id));
	// �o�^����Ă��Ȃ�
	return NULL;
}

int ObjectManager::ProcessInit()
{
	// �폜�\�񂳂�Ă������̂��폜
	// �폜���X�g�ɃI�u�W�F�N�g���o�^���ꂢ�Ă��邩
	if (_vObjctDel.size() > 0) {
		// �폜���X�g�̐擪���擾
		lstObject::iterator ite = _vObjctDel.begin();
		// �폜���X�g�̖����܂Ń��[�v
		for (; ite != _vObjctDel.end(); ++ite) {
			// �I�u�W�F�N�g�̉��
			Release((*ite));
		}
		// �폜���X�g�̃N���A
		_vObjctDel.clear();
	}
	
	// �ǉ����X�g�̂��̂�{���X�g�Ɉړ�
	// �ǉ����X�g�ɃI�u�W�F�N�g���o�^���ꂢ�Ă��邩
	if (_vObjctAdd.size() > 0) {
		// �ǉ����X�g�̐擪���擾
		lstObject::iterator ite = _vObjctAdd.begin();
		// �ǉ����X�g�̖����܂Ń��[�v
		for (; ite != _vObjctAdd.end(); ++ite) {
			// �I�u�W�F�N�g��{���X�g�ɒǉ�
			_vObject.push_back((*ite));
		}
		// �ǉ����X�g�̃N���A
		_vObjctAdd.clear();
	}
	return 0;
}

/*
	@brief ���C���̏���
	@return 0
*/
int ObjectManager::Process()
{
	ProcessInit();

	// obj���X�g�̐擪���擾
	lstObject::iterator ite = _vObject.begin();
	// obj���X�g�̖����܂Ń��[�v
	for (; ite != _vObject.end(); ++ite)
	{
		// �폜���X�g�ɓo�^����Ă��Ȃ���
		if (!IsDelRegister((*ite)))
		{
			// �I�u�W�F�N�g�̍X�V
			(*ite)->Process();

			if(_vObject.empty()) break;
		}
	}
	return 0;
}

/*
	@brief �`��
	@return 0
*/
int ObjectManager::Render()
{
	// obj���X�g�̐擪���擾
	lstObject::iterator ite = _vObject.begin();
	// obj���X�g�̖����܂Ń��[�v
	for (; ite != _vObject.end(); ++ite)
	{
		// �폜���X�g�ɓo�^����Ă��Ȃ���
		if (!IsDelRegister((*ite)))
		{
			// �I�u�W�F�N�g�̕`��
			(*ite)->Render();
		}
	}
	// obj���X�g�̐擪���擾
	lstObject::iterator it = _vObject.begin();
	// obj���X�g�̖����܂Ń��[�v
	for (; it != _vObject.end(); ++it)
	{
		// �폜���X�g�ɓo�^����Ă��Ȃ���
		if (!IsDelRegister((*it)))
		{
			// �I�u�W�F�N�g�̕`��
			(*it)->DebugRenderPos();
		}
	}
	return 0;
}
