
#include "dxlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Mode//ModeServer.h"

// EffekseerForDXLib.hをインクルードします。
#include "EffekseerForDXLib.h"


class ApplicationBase
{
public:
	ApplicationBase();
	virtual ~ApplicationBase();

	virtual bool Initialize(HINSTANCE hInstance);
	virtual bool Terminate();
	virtual bool Input();
	virtual bool Process();
	virtual bool Render();

	virtual bool BeforeDXLib_Init() { return true; }	// DXLib_Init() 実行前に行いたい処理があればオーバーライド

	virtual bool AppWindowed() { return true; }
	virtual int DispSizeW() { return 640; }
	virtual int DispSizeH() { return 480; }

	static	ApplicationBase	*GetInstance() { return _lpInstance; }
	virtual int GetKey() { return _gKey; }
	virtual int GetKey(int plNum) { return _mPad[plNum]._key; }
	virtual int GetTrg() { return _gTrg; }
	virtual int GetTrg(int plNum) { return _mPad[plNum]._trg; }

protected:
	static	ApplicationBase	*_lpInstance;

	int		_gKey, _gTrg;

	// 複数ゲームパッド用の場合
	struct MULTIPAD {
		int _key;			// キー入力の情報
		int _trg;			// トリガ入力の情報
	};
#define	MUTIPAD_MAX		(17)	// 最大で、パッド16個＋キーボードの17個
	MULTIPAD	_mPad[MUTIPAD_MAX];


	ModeServer* _serverMode;

};
