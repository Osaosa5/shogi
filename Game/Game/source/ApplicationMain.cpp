
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"

#ifdef ON_DEBUG
#include "ModeTitle.h"
#else
#include "ModeGame.h"
#endif

// 実体
ApplicationMain				g_oApplicationMain;

bool ApplicationMain::Initialize(HINSTANCE hInstance) {
	if (!base::Initialize(hInstance)) { return false; }

	// アプリケーショングローバルの初期化
	gGlobal.Init();
#ifdef ON_DEBUG
	// モードの登録
	ModeServer::GetInstance()->Add(new ModeTitle(), 1, "Title");
#else
	// モードの登録
	ModeServer::GetInstance()->Add(new ModeGame(), 1, "Game");
#endif

	return true;
}

bool ApplicationMain::Terminate() {
	base::Terminate();
	return true;
}


bool ApplicationMain::Input() {
	base::Input();
	return true;
}

bool ApplicationMain::Process() {
	base::Process();
	return true;
}

bool ApplicationMain::Render() {
	base::Render();
	return true;
}

