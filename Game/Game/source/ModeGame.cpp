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
	if(!base::Initialize()) return false; 

	ResourceManager::Init();
	
	// �I�u�W�F�N�g�Ǘ��𐶐�
	_objectManager = new ObjectManager();
	
	// _objectManager��nullptr�̏ꍇ�͋����I������
	if(!ObjectAdd()) return false;

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

bool ModeGame::ObjectAdd()
{
	if(!_objectManager) return false;

	// �J������ǉ�
	_objectManager->Add(new Camera(), "camera");
	// ���C�g��ǉ�
	_objectManager->Add(new Light(), "light");
	// �����Ղ�ǉ�
	_objectManager->Add(new ShogiBan(), "shogiban");
	// ������ǉ�
	float komaY = 21.0f;
	float komaZPlayer1 = -7.5f;
	auto player1 = Shogi::PLAYER_TYPE::kPlayer1;
	_objectManager->Add(new Fuhyo(_objectManager, VGet(-14.3f, komaY, komaZPlayer1), player1), "fuhyo1");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(-10.6f, komaY, komaZPlayer1), player1), "fuhyo2");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(-7.1f, komaY, komaZPlayer1), player1), "fuhyo3");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(-3.6f, komaY, komaZPlayer1), player1), "fuhyo4");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(-0.1f, komaY, komaZPlayer1), player1), "fuhyo5");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(3.4f, komaY, komaZPlayer1), player1), "fuhyo6");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(7.1f, komaY, komaZPlayer1), player1), "fuhyo7");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(10.6f, komaY, komaZPlayer1), player1), "fuhyo8");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(14.2f, komaY, komaZPlayer1), player1), "fuhyo9");
	float komaZPlayer2 = 7.9f;
	auto player2 = Shogi::PLAYER_TYPE::kPlayer2;
	_objectManager->Add(new Fuhyo(_objectManager, VGet(-14.3f, komaY, komaZPlayer2), player2), "fuhyo10");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(-10.6f, komaY, komaZPlayer2), player2), "fuhyo11");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(-7.1f, komaY, komaZPlayer2), player2), "fuhyo12");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(-3.6f, komaY, komaZPlayer2), player2), "fuhyo13");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(-0.1f, komaY, komaZPlayer2), player2), "fuhyo14");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(3.4f, komaY, komaZPlayer2), player2), "fuhyo15");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(7.1f, komaY, komaZPlayer2), player2), "fuhyo16");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(10.6f, komaY, komaZPlayer2), player2), "fuhyo17");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(14.2f, komaY, komaZPlayer2), player2), "fuhyo18");
	// ���ǉ�
	_objectManager->Add(new Tatami(VGet(44, -10, 15)), "tatami1");
	_objectManager->Add(new Tatami(VGet(-44, -10, 15)), "tatami2");

	return true;
}

