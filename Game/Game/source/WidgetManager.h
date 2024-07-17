#pragma once

#include "appframe.h"
#include "Widget.h"

class WidgetManager
{
	typedef std::vector<Widget*> lstWidget;
public:
	WidgetManager();
	~WidgetManager();

	bool Initialize();
	bool Terminate();
	bool Process();
	bool Render();

	// obj�̒ǉ��E�폜
	int Add(Widget* pObject, const char* name);	// obj�̒ǉ�
	int Del(Widget* pObject);					// obj�̍폜
	void Clear();								// �S�폜

	// obj�̎擾
	Widget* Get(int id);			// id�Ŏ擾
	Widget* Get(const char* name);	// ���O�Ŏ擾

	// id�̎擾
	int GetId(Widget* pObject);		// obj����id���擾
	int GetId(const char* name);	// ���O����id���擾

	// ���O�̎擾
	const char* GetName(Widget* pObject);	// obj���疼�O���擾
	const char* GetName(int id);			// id���疼�O���擾

private:
	int	 Release(Widget* pObject);			// �폜��delete
	bool IsDelRegister(Widget* pObject);	// �폜�o�^����Ă��邩
	bool IsAdd(Widget* pObject);			// �ǉ�����Ă��邩)

	lstWidget	_vWidget;		// �I�u�W�F�N�g���X�g
	int			_idCnt;			// id�J�E���^
	lstWidget	_vWidgetAdd;		// �ǉ����X�g
	lstWidget	_vWidgetDel;		// �폜���X�g
};

