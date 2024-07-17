
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
	// 削除予約されていたものを削除
	// 削除リストにオブジェクトが登録されいているか
	if (_vWidgetDel.size() > 0) {
		// 削除リストの先頭を取得
		lstWidget::iterator ite = _vWidgetDel.begin();
		// 削除リストの末尾までループ
		for (; ite != _vWidgetDel.end(); ++ite) {
			// オブジェクトの解放
			Release((*ite));
		}
		// 削除リストのクリア
		_vWidgetDel.clear();
	}

	// 追加リストのものを本リストに移動
	// 追加リストにオブジェクトが登録されいているか
	if (_vWidgetAdd.size() > 0) {
		// 追加リストの先頭を取得
		lstWidget::iterator ite = _vWidgetAdd.begin();
		// 追加リストの末尾までループ
		for (; ite != _vWidgetAdd.end(); ++ite) {
			// オブジェクトを本リストに追加
			_vWidget.push_back((*ite));
		}
		// 追加リストのクリア
		_vWidgetAdd.clear();
	}

	// objリストの先頭を取得
	lstWidget::iterator ite = _vWidget.begin();
	// objリストの末尾までループ
	for (; ite != _vWidget.end(); ++ite)
	{
		// 削除リストに登録されていないか
		if (!IsDelRegister((*ite)))
		{
			// オブジェクトの更新
			(*ite)->Process();

			if (_vWidget.empty()) break;
		}
	}
	return true;
}

bool WidgetManager::Render()
{
	// objリストの先頭を取得
	lstWidget::iterator ite = _vWidget.begin();
	// objリストの末尾までループ
	for (; ite != _vWidget.end(); ++ite)
	{
		// 削除リストに登録されていないか
		if (!IsDelRegister((*ite)))
		{
			// オブジェクトの描画
			(*ite)->Render();

			if (_vWidget.empty()) break;
		}
	}
	return true;
}

int WidgetManager::Add(Widget* ptrWidget, const char* name)
{
	// 追加リストに登録されているか
	if (IsAdd(ptrWidget)) return -1;

	// idの設定
	ptrWidget->_id = _idCnt;
	// 名前の設定
	ptrWidget->_name = name;

	// 追加リストに登録
	_vWidgetAdd.emplace_back(ptrWidget);

	// idカウンタのインクリメント
	_idCnt++;

	return 0;
}

int WidgetManager::Del(Widget* ptrWidget)
{
	// 削除リストに登録されているか
	if (IsDelRegister(ptrWidget)) return -1;

	// 削除リストに登録
	_vWidgetDel.emplace_back(ptrWidget);

	return 0;
}

void WidgetManager::Clear()
{
	// objリストの先頭を取得
	lstWidget::iterator ite = _vWidget.begin();
	// objリストの末尾までループ
	for (; ite != _vWidget.end(); ++ite)
	{
		// オブジェクトの解放
		Release((*ite));
	}
	// objリストのクリア
	_vWidget.clear();
}

Widget* WidgetManager::Get(int id)
{
	// objリストの先頭を取得
	lstWidget::iterator ite = _vWidget.begin();
	// objリストの末尾までループ
	for (; ite != _vWidget.end(); ++ite)
	{
		// idが一致したら
		if ((*ite)->_id == id)
		{
			// オブジェクトを返す
			return (*ite);
		}
	}
	// 見つからなかったらNULLを返す
	return nullptr;
}

Widget* WidgetManager::Get(const char* name)
{
	// objリストの先頭を取得
	lstWidget::iterator ite = _vWidget.begin();
	// objリストの末尾までループ
	for (; ite != _vWidget.end(); ++ite)
	{
		// 名前が一致したら
		if ((*ite)->_name == name)
		{
			// オブジェクトを返す
			return (*ite);
		}
	}
	// 見つからなかったらNULLを返す
	return nullptr;
}

int WidgetManager::GetId(Widget* ptrWidget)
{
	// objリストの先頭を取得
	lstWidget::iterator ite = _vWidget.begin();
	// objリストの末尾までループ
	for (; ite != _vWidget.end(); ++ite)
	{
		// objが一致したら
		if ((*ite) == ptrWidget)
		{
			// idを返す
			return (*ite)->_id;
		}
	}
	// 見つからなかったら-1を返す
	return -1;
}

int WidgetManager::GetId(const char* name)
{
	// objリストの先頭を取得
	lstWidget::iterator ite = _vWidget.begin();
	// objリストの末尾までループ
	for (; ite != _vWidget.end(); ++ite)
	{
		// 名前が一致したら
		if ((*ite)->_name == name)
		{
			// idを返す
			return (*ite)->_id;
		}
	}
	// 見つからなかったら-1を返す
	return -1;
}

const char* WidgetManager::GetName(Widget* ptrWidget)
{
	// objリストの先頭を取得
	lstWidget::iterator ite = _vWidget.begin();
	// objリストの末尾までループ
	for (; ite != _vWidget.end(); ++ite)
	{
		// objが一致したら
		if ((*ite) == ptrWidget)
		{
			// 名前を返す
			return (*ite)->_name.c_str();
		}
	}
	// 見つからなかったらNULLを返す
	return nullptr;
}

const char* WidgetManager::GetName(int id)
{
	// objリストの先頭を取得
	lstWidget::iterator ite = _vWidget.begin();
	// objリストの末尾までループ
	for (; ite != _vWidget.end(); ++ite)
	{
		// idが一致したら
		if ((*ite)->_id == id)
		{
			// 名前を返す
			return (*ite)->_name.c_str();
		}
	}
	// 見つからなかったらNULLを返す
	return nullptr;
}

int WidgetManager::Release(Widget* ptrWidget)
{
	// objリストの先頭を取得
	lstWidget::iterator ite = _vWidget.begin();
	// objリストの末尾までループ
	for (; ite != _vWidget.end(); ++ite)
	{
		// objが一致したら
		if ((*ite) == ptrWidget)
		{
			// オブジェクトの解放
			delete (*ite);
			// objリストから削除
			_vWidget.erase(ite);
			// 正常終了
			return 0;
		}
	}
	// 見つからなかったら-1を返す
	return -1;
}

bool WidgetManager::IsDelRegister(Widget* ptrWidget)
{
	// 削除リストの先頭を取得
	lstWidget::iterator ite = _vWidgetDel.begin();
	// 削除リストの末尾までループ
	for (; ite != _vWidgetDel.end(); ++ite)
	{
		// objが一致したら
		if ((*ite) == ptrWidget)
		{
			// 登録されている
			return true;
		}
	}
	// 登録されていない
	return false;
}

bool WidgetManager::IsAdd(Widget* ptrWidget)
{
	// objリストの先頭を取得
	lstWidget::iterator ite = _vWidget.begin();
	// objリストの末尾までループ
	for (; ite != _vWidget.end(); ++ite)
	{
		// objが一致したら
		if ((*ite) == ptrWidget)
		{
			// 登録されている
			return true;
		}
	}
	// 追加リストの先頭を取得
	ite = _vWidgetAdd.begin();
	// 追加リストの末尾までループ
	for (; ite != _vWidgetAdd.end(); ++ite)
	{
		// objが一致したら
		if ((*ite) == ptrWidget)
		{
			// 登録されている
			return true;
		}
	}
	// 登録されていない
	return false;
}