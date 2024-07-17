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

	// objの追加・削除
	int Add(Widget* pObject, const char* name);	// objの追加
	int Del(Widget* pObject);					// objの削除
	void Clear();								// 全削除

	// objの取得
	Widget* Get(int id);			// idで取得
	Widget* Get(const char* name);	// 名前で取得

	// idの取得
	int GetId(Widget* pObject);		// objからidを取得
	int GetId(const char* name);	// 名前からidを取得

	// 名前の取得
	const char* GetName(Widget* pObject);	// objから名前を取得
	const char* GetName(int id);			// idから名前を取得

private:
	int	 Release(Widget* pObject);			// 削除＆delete
	bool IsDelRegister(Widget* pObject);	// 削除登録されているか
	bool IsAdd(Widget* pObject);			// 追加されているか)

	lstWidget	_vWidget;		// オブジェクトリスト
	int			_idCnt;			// idカウンタ
	lstWidget	_vWidgetAdd;		// 追加リスト
	lstWidget	_vWidgetDel;		// 削除リスト
};

