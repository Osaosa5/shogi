#include "ObjectManager.h"
#include "Object.h"

/*
	@brief コンストラクタ
*/
ObjectManager::ObjectManager()
{
	_idCnt = 1;
}

/*
	@brief デストラクタ
*/
ObjectManager::~ObjectManager()
{
	Clear();
}

/*
	@brief オブジェクトの追加
	@param pObject：追加するオブジェクト
	@param name：オブジェクトの登録名
	@return 追加したオブジェクトのID
*/
int ObjectManager::Add(Object* pObject, const char* name)
{
	// 追加リストに登録
	_vObjctAdd.push_back(pObject);
	// IDを設定
	pObject->_id = _idCnt;
	// IDをインクリメント
	_idCnt++;
	// 名前を設定
	pObject->_name = name;
	// idを返す
	return pObject->_id;
}

/*
	@brief オブジェクトの削除
	@param pObject：削除するオブジェクト
	@return 0
*/
int ObjectManager::Del(Object* pObject)
{
	// 削除リストに登録
	_vObjctDel.push_back(pObject);
	return 0;
}

/*
	@brief オブジェクトの解放
	@param pObject：解放するオブジェクト
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
	@brief オブジェクトの全削除
*/
void ObjectManager::Clear()
{
	// objリストの末尾を取得
	lstObject::reverse_iterator ite = _vObject.rbegin();
	// objリストの先頭までループ
	for(; ite != _vObject.rend(); ++ite)
	{
		// オブジェクトの終了処理
		(*ite)->Terminate();
		// オブジェクトの削除
		delete (*ite);
	}
	// 追加オブジェクトの先頭を取得
	lstObject::iterator iteAdd = _vObjctAdd.begin();
	// 追加オブジェクトの末尾までループ
	for(; iteAdd != _vObjctAdd.end(); ++iteAdd)
	{
		// オブジェクトの終了処理
		(*iteAdd)->Terminate();
		// オブジェクトの削除
		delete (*iteAdd);
	}
	// リストのクリア
	_vObject.clear();
	_vObjctAdd.clear();
	_vObjctDel.clear();
}

/*
	@brief 削除予約の確認
*/
bool ObjectManager::IsDelRegister(Object* pObject)
{
	// 削除リストに登録されているか
	if (_vObjctDel.size() > 0) {
		// 削除リストの先頭を取得
		lstObject::iterator ite = _vObjctDel.begin();
		// 削除リストの末尾までループ
		for (; ite != _vObjctDel.end(); ++ite) {
			// 削除リストに登録されているか
			if ((*ite) == pObject) return true;
		}
	}
	// 登録されていない
	return false;
}

/*
	@brief オブジェクトの登録確認
	@param pObject：登録確認するオブジェクト
	@return true：登録されている
	@return false：登録されていない
*/
bool ObjectManager::IsAdd(Object* pObject)
{
	// objリストの先頭を取得
	lstObject::iterator ite = _vObject.begin();
	// objリストの末尾までループ
	for(; ite != _vObject.end(); ++ite)
	{
		// 登録されていたらtrueを返す
		if(!IsDelRegister((*ite)) && (*ite) == pObject) return true;
	}

	// 追加リストの先頭を取得
	ite = _vObjctAdd.begin();
	// 追加リストの末尾までループ
	for (; ite != _vObjctAdd.end(); ++ite)
	{
		// 登録されていたらtrueを返す
		if(!IsDelRegister((*ite)) && (*ite) == pObject) return true;
	}
	// 登録されていない
	return false;
}

/*
	@brief オブジェクトIDから検索
	@param id：検索するオブジェクトID
	@return 検索したオブジェクト
	@return NULL：見つからなかった
*/
Object *ObjectManager::Get(int id)
{
	// objリストの先頭を取得
	lstObject::iterator ite = _vObject.begin();
	// objリストの末尾までループ
	for (; ite != _vObject.end(); ++ite)
	{
		// idが一致したらそのオブジェクトを返す
		if(!IsDelRegister((*ite)) && (*ite)->_id == id) return (*ite);
	}

	// 追加リストの先頭を取得
	ite = _vObjctAdd.begin();
	// 追加リストの末尾までループ
	for (; ite != _vObjctAdd.end(); ++ite)
	{
		// idが一致したらそのオブジェクトを返す
		if(!IsDelRegister((*ite)) && (*ite)->_id == id) return (*ite);
	}
	// 見つからなかった
	return NULL;
}

/*
	@brief オブジェクト名から検索
	@param name：検索するオブジェクト名
	@return 検索したオブジェクト
	@return NULL：見つからなかった
*/
Object *ObjectManager::Get(const char* name)
{
	// objリストの先頭を取得
	lstObject::iterator ite = _vObject.begin();
	// objリストの末尾までループ
	for (; ite != _vObject.end(); ++ite)
	{
		// 名前が一致したらそのオブジェクトを返す
		if(!IsDelRegister((*ite)) && (*ite)->_name == name) return (*ite);
	}

	// 追加リストの先頭を取得
	ite = _vObjctAdd.begin();
	// 追加リストの末尾までループ
	for (; ite != _vObjctAdd.end(); ++ite)
	{
		// 名前が一致したらそのオブジェクトを返す
		if(!IsDelRegister((*ite)) && (*ite)->_name == name) return (*ite);
	}
	// 見つからなかった
	return NULL;
}

/*
	@brief オブジェクトIDの取得
	@param pObject：IDを取得するオブジェクト
	@return ID：オブジェクトID
	@return 0：見つからなかった
*/
int ObjectManager::GetId(Object* pObject)
{
	// 登録されているか	IDを返す
	if (IsAdd(pObject)) return pObject->_id;
	// 登録されていない	
	return 0;
}

/*
	@brief オブジェクトIDの取得
	@param name：IDを取得するオブジェクト名
	@return ID：オブジェクトID
	@return 0：見つからなかった
*/
int ObjectManager::GetId(const char* name)
{
	// IDを取得
	return GetId(Get(name));
}

/*
	@brief オブジェクト名の取得
	@param pObject：名前を取得するオブジェクト
	@return 名前：オブジェクト名
	@return NULL：見つからなかった
*/
const char *ObjectManager::GetName(Object* pObject)
{
	// 登録されているか
	if(IsAdd(pObject)) return pObject->_name.c_str();
	// 登録されていない
	return NULL;
}

/*
	@brief オブジェクト名の取得
	@param id：名前を取得するオブジェクトID
	@return 名前：オブジェクト名
	@return NULL：見つからなかった
*/
const char *ObjectManager::GetName(int id)
{
	// 名前を取得
	return GetName(Get(id));
	// 登録されていない
	return NULL;
}

int ObjectManager::ProcessInit()
{
	// 削除予約されていたものを削除
	// 削除リストにオブジェクトが登録されいているか
	if (_vObjctDel.size() > 0) {
		// 削除リストの先頭を取得
		lstObject::iterator ite = _vObjctDel.begin();
		// 削除リストの末尾までループ
		for (; ite != _vObjctDel.end(); ++ite) {
			// オブジェクトの解放
			Release((*ite));
		}
		// 削除リストのクリア
		_vObjctDel.clear();
	}
	
	// 追加リストのものを本リストに移動
	// 追加リストにオブジェクトが登録されいているか
	if (_vObjctAdd.size() > 0) {
		// 追加リストの先頭を取得
		lstObject::iterator ite = _vObjctAdd.begin();
		// 追加リストの末尾までループ
		for (; ite != _vObjctAdd.end(); ++ite) {
			// オブジェクトを本リストに追加
			_vObject.push_back((*ite));
		}
		// 追加リストのクリア
		_vObjctAdd.clear();
	}
	return 0;
}

/*
	@brief メインの処理
	@return 0
*/
int ObjectManager::Process()
{
	ProcessInit();

	// objリストの先頭を取得
	lstObject::iterator ite = _vObject.begin();
	// objリストの末尾までループ
	for (; ite != _vObject.end(); ++ite)
	{
		// 削除リストに登録されていないか
		if (!IsDelRegister((*ite)))
		{
			// オブジェクトの更新
			(*ite)->Process();

			if(_vObject.empty()) break;
		}
	}
	return 0;
}

/*
	@brief 描画
	@return 0
*/
int ObjectManager::Render()
{
	// objリストの先頭を取得
	lstObject::iterator ite = _vObject.begin();
	// objリストの末尾までループ
	for (; ite != _vObject.end(); ++ite)
	{
		// 削除リストに登録されていないか
		if (!IsDelRegister((*ite)))
		{
			// オブジェクトの描画
			(*ite)->Render();
		}
	}
	// objリストの先頭を取得
	lstObject::iterator it = _vObject.begin();
	// objリストの末尾までループ
	for (; it != _vObject.end(); ++it)
	{
		// 削除リストに登録されていないか
		if (!IsDelRegister((*it)))
		{
			// オブジェクトの描画
			(*it)->DebugRenderPos();
		}
	}
	return 0;
}
