
#include "ApplicationBase.h"

ApplicationBase	*ApplicationBase::_lpInstance = NULL;


ApplicationBase::ApplicationBase() {
	_lpInstance = this;
}

ApplicationBase::~ApplicationBase() {
}

bool ApplicationBase::Initialize(HINSTANCE hInstance) {

	// DXライブラリの初期化
	if(AppWindowed()){
		ChangeWindowMode(true);							// ウィンドウモードに指定する
		SetWindowSizeChangeEnableFlag(true);				// ウィンドウサイズ変更を許可する
	}
	SetGraphMode(DispSizeW(), DispSizeH(), 32);

	// DirectX11を使用するようにする。(DirectX9も可、一部機能不可)
	// Effekseerを使用するには必ず設定する。
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// 距離が近いところでチラツキが発生する（Z深度が足りない）対策
	SetZBufferBitDepth(32);

	// アプリ側でDXLib_Init()前にやりたい処理を呼ぶ
	if (!BeforeDXLib_Init()) {
		return false;
	}

	if (DxLib_Init() == -1)
	{	// エラーが起きたら直ちに終了
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);		// 描画先画面を裏画面にセット

	// Effekseerを初期化する。
	// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return false;
	}

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DXライブラリのデバイスロストした時のコールバックを設定する。
	// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
	// ただし、DirectX11を使用する場合は実行する必要はない。
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// 乱数初期化
	srand((unsigned int)time(NULL));

	// モードサーバの初期化
	_serverMode = new ModeServer();

	return true;
}

bool ApplicationBase::Terminate() {
	// Effekseerを終了する。
	Effkseer_End();

	// DXライブラリ開放
	DxLib_End();

	return true;
}


bool ApplicationBase::Input() {
	// キーの入力、トリガ入力を得る
	int keyold = _gKey;
	_gKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	_gTrg = (_gKey ^ keyold) & _gKey;	// キーのトリガ情報生成（押した瞬間しか反応しないキー情報）

	// 複数ゲームパッド用
	int padTbl[] = {
		DX_INPUT_KEY,	// 0:キー入力
		DX_INPUT_PAD1,	// 1:パッド1
		DX_INPUT_PAD2,	// 2:パッド2
		DX_INPUT_PAD3,	// 3:パッド3
		DX_INPUT_PAD4,	// 4:パッド4
		DX_INPUT_PAD5,	// 5:パッド5
		DX_INPUT_PAD6,	// 6:パッド6
		DX_INPUT_PAD7,	// 7:パッド7
		DX_INPUT_PAD8,	// 8:パッド8
		DX_INPUT_PAD9,	// 9:パッド9
		DX_INPUT_PAD10,	// 10:パッド10
		DX_INPUT_PAD11,	// 11:パッド11
		DX_INPUT_PAD12,	// 12:パッド12
		DX_INPUT_PAD13,	// 13:パッド13
		DX_INPUT_PAD14,	// 14:パッド14
		DX_INPUT_PAD15,	// 15:パッド15
		DX_INPUT_PAD16,	// 16:パッド16
	};
	for (int i = 0; i < MUTIPAD_MAX; i++) {
		int keyold = _mPad[i]._key;
		_mPad[i]._key = GetJoypadInputState(padTbl[i]);
		_mPad[i]._trg = (_mPad[i]._key ^ keyold) & _mPad[i]._key;
	}

	return true;
}

bool ApplicationBase::Process() {
	_serverMode->ProcessInit();
	_serverMode->Process();
	_serverMode->ProcessFinish();
	return true;
}

bool ApplicationBase::Render() {
	_serverMode->RenderInit();
	_serverMode->Render();
	_serverMode->RenderFinish();
	return true;
}
