/*
 ModeEnd.cpp
 �쐬���F2024/05/21
 �ҏW���F2024/05/21
 �T�v�F�Q�[���I����̉�ʂ�\�����郂�[�h
*/

#include "AppFrame.h"
#include "ApplicationMain.h"

#include "ModeEnd.h"
#include "ModeTitle.h"

bool ModeEnd::Initialize()
{
	if (!base::Initialize()) { return false; }
	return true;
}

bool ModeEnd::Terminate()
{
	base::Terminate();
	return true;
}

bool ModeEnd::Process()
{
	base::Process();

	// ���͏����擾
	auto app = ApplicationMain::GetInstance();
	int trg = app->GetTrg();

	// Z�L�[�������ꂽ��^�C�g���ɖ߂�
	if (trg & PAD_INPUT_1) {
		auto mdServer = ModeServer::GetInstance();
		mdServer->Del(this);
		mdServer->Add(new ModeTitle(), 1, "Title");
	}

	return true;
}

bool ModeEnd::Render()
{
	base::Render();

	// ���[�h����\��
	std::string name = ModeServer::GetInstance()->GetName(this);
	DrawFormatString(0, 0, GetColor(255, 255, 255), name.c_str());

	return true;
}
