/*
 ModeTitle.cpp
 �쐬���F2024/05/21
 �ҏW���F2024/05/21
 �T�v�F�^�C�g����ʂ�\�����郂�[�h
*/

#include "AppFrame.h"
#include "ApplicationMain.h"

#include "ModeTitle.h"
#include "ModeGame.h"

bool ModeTitle::Initialize()
{
	if (!base::Initialize()) { return false; }
	return true;
}

bool ModeTitle::Terminate()
{
	base::Terminate();
	return true;
}

bool ModeTitle::Process()
{
	base::Process();

	// ���͏����擾
	auto app = ApplicationMain::GetInstance();
	int trg = app->GetTrg();

	// Z�L�[�������ꂽ��Q�[�����[�h�ɑJ��
	if (trg & PAD_INPUT_1) {
		auto mdServer = ModeServer::GetInstance();
		mdServer->Del(this);
		mdServer->Add(new ModeGame(), 1, "game");
	}

	return true;
}

bool ModeTitle::Render()
{
	base::Render();

	// ���[�h����\��
	std::string name = ModeServer::GetInstance()->GetName(this);
	DrawFormatString(0, 0, GetColor(255, 255, 255), name.c_str());

	return true;
}
