
#include "WidgetManager.h"

WidgetManager::WidgetManager()
{
	_idCnt = 1;
}

WidgetManager::~WidgetManager()
{
}

bool WidgetManager::Initialize()
{
	return true;
}

bool WidgetManager::Terminate()
{
	Clear();
	return true;
}

bool WidgetManager::Process()
{
	// �폜�\�񂳂�Ă������̂��폜
	// �폜���X�g�ɃI�u�W�F�N�g���o�^���ꂢ�Ă��邩
	if (_vWidgetDel.size() > 0) {
		// �폜���X�g�̐擪���擾
		lstWidget::iterator ite = _vWidgetDel.begin();
		// �폜���X�g�̖����܂Ń��[�v
		for (; ite != _vWidgetDel.end(); ++ite) {
			// �I�u�W�F�N�g�̉��
			Release((*ite));
		}
		// �폜���X�g�̃N���A
		_vWidgetDel.clear();
	}

	// �ǉ����X�g�̂��̂�{���X�g�Ɉړ�
	// �ǉ����X�g�ɃI�u�W�F�N�g���o�^���ꂢ�Ă��邩
	if (_vWidgetAdd.size() > 0) {
		// �ǉ����X�g�̐擪���擾
		lstWidget::iterator ite = _vWidgetAdd.begin();
		// �ǉ����X�g�̖����܂Ń��[�v
		for (; ite != _vWidgetAdd.end(); ++ite) {
			// �I�u�W�F�N�g��{���X�g�ɒǉ�
			_vWidget.push_back((*ite));
		}
		// �ǉ����X�g�̃N���A
		_vWidgetAdd.clear();
	}

	// obj���X�g�̐擪���擾
	lstWidget::iterator ite = _vWidget.begin();
	// obj���X�g�̖����܂Ń��[�v
	for (; ite != _vWidget.end(); ++ite)
	{
		// �폜���X�g�ɓo�^����Ă��Ȃ���
		if (!IsDelRegister((*ite)))
		{
			// �I�u�W�F�N�g�̍X�V
			(*ite)->Process();

			if (_vWidget.empty()) break;
		}
	}
	return true;
}

bool WidgetManager::Render()
{
	// obj���X�g�̐擪���擾
	lstWidget::iterator ite = _vWidget.begin();
	// obj���X�g�̖����܂Ń��[�v
	for (; ite != _vWidget.end(); ++ite)
	{
		// �폜���X�g�ɓo�^����Ă��Ȃ���
		if (!IsDelRegister((*ite)))
		{
			// �I�u�W�F�N�g�̕`��
			(*ite)->Render();

			if (_vWidget.empty()) break;
		}
	}
	return true;
}

int WidgetManager::Add(Widget* ptrWidget, const char* name)
{
	// �ǉ����X�g�ɓo�^����Ă��邩
	if (IsAdd(ptrWidget)) return -1;

	// id�̐ݒ�
	ptrWidget->_id = _idCnt;
	// ���O�̐ݒ�
	ptrWidget->_name = name;

	// �ǉ����X�g�ɓo�^
	_vWidgetAdd.emplace_back(ptrWidget);

	// id�J�E���^�̃C���N�������g
	_idCnt++;

	return 0;
}

int WidgetManager::Del(Widget* ptrWidget)
{
	// �폜���X�g�ɓo�^����Ă��邩
	if (IsDelRegister(ptrWidget)) return -1;

	// �폜���X�g�ɓo�^
	_vWidgetDel.emplace_back(ptrWidget);

	return 0;
}

void WidgetManager::Clear()
{
	// obj���X�g�̐擪���擾
	lstWidget::iterator ite = _vWidget.begin();
	// obj���X�g�̖����܂Ń��[�v
	for (; ite != _vWidget.end(); ++ite)
	{
		// �I�u�W�F�N�g�̉��
		Release((*ite));
	}
	// obj���X�g�̃N���A
	_vWidget.clear();
}

Widget* WidgetManager::Get(int id)
{
	// obj���X�g�̐擪���擾
	lstWidget::iterator ite = _vWidget.begin();
	// obj���X�g�̖����܂Ń��[�v
	for (; ite != _vWidget.end(); ++ite)
	{
		// id����v������
		if ((*ite)->_id == id)
		{
			// �I�u�W�F�N�g��Ԃ�
			return (*ite);
		}
	}
	// ������Ȃ�������NULL��Ԃ�
	return nullptr;
}

Widget* WidgetManager::Get(const char* name)
{
	// obj���X�g�̐擪���擾
	lstWidget::iterator ite = _vWidget.begin();
	// obj���X�g�̖����܂Ń��[�v
	for (; ite != _vWidget.end(); ++ite)
	{
		// ���O����v������
		if ((*ite)->_name == name)
		{
			// �I�u�W�F�N�g��Ԃ�
			return (*ite);
		}
	}
	// ������Ȃ�������NULL��Ԃ�
	return nullptr;
}

int WidgetManager::GetId(Widget* ptrWidget)
{
	// obj���X�g�̐擪���擾
	lstWidget::iterator ite = _vWidget.begin();
	// obj���X�g�̖����܂Ń��[�v
	for (; ite != _vWidget.end(); ++ite)
	{
		// obj����v������
		if ((*ite) == ptrWidget)
		{
			// id��Ԃ�
			return (*ite)->_id;
		}
	}
	// ������Ȃ�������-1��Ԃ�
	return -1;
}

int WidgetManager::GetId(const char* name)
{
	// obj���X�g�̐擪���擾
	lstWidget::iterator ite = _vWidget.begin();
	// obj���X�g�̖����܂Ń��[�v
	for (; ite != _vWidget.end(); ++ite)
	{
		// ���O����v������
		if ((*ite)->_name == name)
		{
			// id��Ԃ�
			return (*ite)->_id;
		}
	}
	// ������Ȃ�������-1��Ԃ�
	return -1;
}

const char* WidgetManager::GetName(Widget* ptrWidget)
{
	// obj���X�g�̐擪���擾
	lstWidget::iterator ite = _vWidget.begin();
	// obj���X�g�̖����܂Ń��[�v
	for (; ite != _vWidget.end(); ++ite)
	{
		// obj����v������
		if ((*ite) == ptrWidget)
		{
			// ���O��Ԃ�
			return (*ite)->_name.c_str();
		}
	}
	// ������Ȃ�������NULL��Ԃ�
	return nullptr;
}

const char* WidgetManager::GetName(int id)
{
	// obj���X�g�̐擪���擾
	lstWidget::iterator ite = _vWidget.begin();
	// obj���X�g�̖����܂Ń��[�v
	for (; ite != _vWidget.end(); ++ite)
	{
		// id����v������
		if ((*ite)->_id == id)
		{
			// ���O��Ԃ�
			return (*ite)->_name.c_str();
		}
	}
	// ������Ȃ�������NULL��Ԃ�
	return nullptr;
}

int WidgetManager::Release(Widget* ptrWidget)
{
	// obj���X�g�̐擪���擾
	lstWidget::iterator ite = _vWidget.begin();
	// obj���X�g�̖����܂Ń��[�v
	for (; ite != _vWidget.end(); ++ite)
	{
		// obj����v������
		if ((*ite) == ptrWidget)
		{
			// �I�u�W�F�N�g�̉��
			delete (*ite);
			// obj���X�g����폜
			_vWidget.erase(ite);
			// ����I��
			return 0;
		}
	}
	// ������Ȃ�������-1��Ԃ�
	return -1;
}

bool WidgetManager::IsDelRegister(Widget* ptrWidget)
{
	// �폜���X�g�̐擪���擾
	lstWidget::iterator ite = _vWidgetDel.begin();
	// �폜���X�g�̖����܂Ń��[�v
	for (; ite != _vWidgetDel.end(); ++ite)
	{
		// obj����v������
		if ((*ite) == ptrWidget)
		{
			// �o�^����Ă���
			return true;
		}
	}
	// �o�^����Ă��Ȃ�
	return false;
}

bool WidgetManager::IsAdd(Widget* ptrWidget)
{
	// obj���X�g�̐擪���擾
	lstWidget::iterator ite = _vWidget.begin();
	// obj���X�g�̖����܂Ń��[�v
	for (; ite != _vWidget.end(); ++ite)
	{
		// obj����v������
		if ((*ite) == ptrWidget)
		{
			// �o�^����Ă���
			return true;
		}
	}
	// �ǉ����X�g�̐擪���擾
	ite = _vWidgetAdd.begin();
	// �ǉ����X�g�̖����܂Ń��[�v
	for (; ite != _vWidgetAdd.end(); ++ite)
	{
		// obj����v������
		if ((*ite) == ptrWidget)
		{
			// �o�^����Ă���
			return true;
		}
	}
	// �o�^����Ă��Ȃ�
	return false;
}