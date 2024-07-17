
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"

#ifdef ON_DEBUG
#include "ModeTitle.h"
#else
#include "ModeGame.h"
#endif

// ����
ApplicationMain				g_oApplicationMain;

bool ApplicationMain::Initialize(HINSTANCE hInstance) {
	if (!base::Initialize(hInstance)) { return false; }

	// �A�v���P�[�V�����O���[�o���̏�����
	gGlobal.Init();
#ifdef ON_DEBUG
	// ���[�h�̓o�^
	ModeServer::GetInstance()->Add(new ModeTitle(), 1, "Title");
#else
	// ���[�h�̓o�^
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

