/*
 ModeGame.cpp
 �쐬���F2024/05/21
 �ҏW���F2024/05/21
 �T�v�F���ۂɃQ�[�����v���C���郂�[�h
*/

#include "AppFrame.h"
#include "ApplicationMain.h"

#include "ModeGame.h"
#include "ModeEnd.h"

#include "ObjectManager.h"
#include "Camera.h"
#include "Light.h"
#include "ShogiBan.h"
#include "Tatami.h"
#include "Fuhyo.h"

bool ModeGame::Initialize()
{
	if (!base::Initialize()) { return false; }

	ResourceManager::Init();

	// �I�u�W�F�N�g�Ǘ��𐶐�
	_objectManager = new ObjectManager();
	// �J������ǉ�
	_objectManager->Add(new Camera(),"camera");
	// ���C�g��ǉ�
	_objectManager->Add(new Light(), "light");
	// �����Ղ�ǉ�
	_objectManager->Add(new ShogiBan(), "shogiban");
	// ������ǉ�
	_objectManager->Add(new Fuhyo(_objectManager), "fuhyo1");
	// ���ǉ�
	_objectManager->Add(new Tatami(VGet(44,-10,15)), "tatami1");
	_objectManager->Add(new Tatami(VGet(-44, -10, 15)), "tatami2");

	return true;
}

bool ModeGame::Terminate() 
{
	base::Terminate();

	ResourceManager::Release();

	// �I�u�W�F�N�g�Ǘ����폜
	delete _objectManager;

	return true;
}

bool ModeGame::Process() 
{
	base::Process();

	// ���͏����擾
	auto app = ApplicationMain::GetInstance();
	int trg = app->GetTrg();

	// Z�L�[�������ꂽ��I�����[�h�ɑJ��
	if (trg & PAD_INPUT_1) {
		auto mdServer = ModeServer::GetInstance();
		mdServer->Del(this);
		mdServer->Add(new ModeEnd(),1,"end");
	}

	// �I�u�W�F�N�g���X�V
	_objectManager->Process();

	return true;
}

bool ModeGame::Render() 
{
	base::Render();

	// �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);

	// �I�u�W�F�N�g��`��
	_objectManager->Render();

	// ���[�h����\��
	std::string name = ModeServer::GetInstance()->GetName(this);
	DrawFormatString(0, 0, GetColor(255, 255, 255), name.c_str());

	return true;
}

