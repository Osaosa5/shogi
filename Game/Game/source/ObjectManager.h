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

	// objの追加・削除
	int Add(Object *pObject, const char *name);	// objの追加
	int Del(Object *pObject);					// objの削除
	void Clear();								// 全削除

	// objの取得
	Object *Get(int id);			// idで取得
	Object *Get(const char *name);	// 名前で取得

	// idの取得
	int GetId(Object* pObject);		// objからidを取得
	int GetId(const char *name);	// 名前からidを取得

	// 名前の取得
	const char *GetName(Object* pObject);	// objから名前を取得
	const char *GetName(int id);			// idから名前を取得

	// メインの処理
	int ProcessInit();	// プロセスを回すための初期化
	int Process();		// プロセスを回す

	// 描画
	int Render();		// 描画

private:
	int	 Release(Object *pObject);			// 削除＆delete
	bool IsDelRegister(Object *pObject);	// 削除登録されているか
	bool IsAdd(Object *pObject);			// 追加されているか)

	lstObject	_vObject;		// オブジェクトリスト
	int			_idCnt;			// idカウンタ
	lstObject	_vObjctAdd;		// 追加リスト
	lstObject	_vObjctDel;		// 削除リスト
};

