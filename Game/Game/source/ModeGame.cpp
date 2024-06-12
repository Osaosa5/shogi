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
#include "Lance.h"
#include "Knight.h"
#include "SilverGeneral.h"
#include "GoldGeneral.h"

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

	// ���Y���W
	float komaY = 21.0f;
	// player1�̋�
	auto player1 = Shogi::PLAYER_TYPE::kPlayer1;
	// ������ǉ�
	float sevenRow = -7.5f;
	_objectManager->Add(new Fuhyo(_objectManager, VGet(-14.3f, komaY, sevenRow), player1), "fuhyo1");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(-10.6f, komaY, sevenRow), player1), "fuhyo2");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(-7.1f,  komaY, sevenRow), player1), "fuhyo3");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(-3.6f,  komaY, sevenRow), player1), "fuhyo4");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(-0.1f,  komaY, sevenRow), player1), "fuhyo5");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(3.4f,   komaY, sevenRow), player1), "fuhyo6");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(7.1f,   komaY, sevenRow), player1), "fuhyo7");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(10.6f,  komaY, sevenRow), player1), "fuhyo8");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(14.2f,  komaY, sevenRow), player1), "fuhyo9");
	// ���Ԃ�ǉ�
	float nineRow = -15.4f;
	_objectManager->Add(new Lance(_objectManager, VGet(-14.3f, komaY, nineRow), player1), "lance1");
	_objectManager->Add(new Lance(_objectManager, VGet(14.2f,  komaY, nineRow), player1), "lance2");
	// �j�n��ǉ�
	_objectManager->Add(new Knight(_objectManager, VGet(-10.6f, komaY, nineRow), player1), "knight1");
	_objectManager->Add(new Knight(_objectManager, VGet(10.6f,  komaY, nineRow), player1), "knight2");
	// �⏫��ǉ�
	_objectManager->Add(new SilverGeneral(_objectManager, VGet(-7.1f, komaY, nineRow), player1), "silver1");
	_objectManager->Add(new SilverGeneral(_objectManager, VGet(7.1f,  komaY, nineRow), player1), "silver2");
	// ������ǉ�
	_objectManager->Add(new GoldGeneral(_objectManager, VGet(-3.6f, komaY, nineRow), player1), "gold1");
	_objectManager->Add(new GoldGeneral(_objectManager, VGet(3.4f,  komaY, nineRow), player1), "gold2");

	// player2�̋�
	auto player2 = Shogi::PLAYER_TYPE::kPlayer2;
	// ������ǉ�
	float threeRow = 7.9f;
	_objectManager->Add(new Fuhyo(_objectManager, VGet(-14.3f, komaY, threeRow), player2), "fuhyo10");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(-10.6f, komaY, threeRow), player2), "fuhyo11");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(-7.1f,  komaY, threeRow), player2), "fuhyo12");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(-3.6f,  komaY, threeRow), player2), "fuhyo13");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(-0.1f,  komaY, threeRow), player2), "fuhyo14");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(3.4f,   komaY, threeRow), player2), "fuhyo15");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(7.1f,   komaY, threeRow), player2), "fuhyo16");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(10.6f,  komaY, threeRow), player2), "fuhyo17");
	_objectManager->Add(new Fuhyo(_objectManager, VGet(14.2f,  komaY, threeRow), player2), "fuhyo18");
	// ���Ԃ�ǉ�
	float oneRow = 15.7f;
	_objectManager->Add(new Lance(_objectManager, VGet(-14.3f, komaY, oneRow), player2), "lance3");
	_objectManager->Add(new Lance(_objectManager, VGet(14.2f,  komaY, oneRow), player2), "lance4");
	// �j�n��ǉ�
	_objectManager->Add(new Knight(_objectManager, VGet(-10.6f, komaY, oneRow), player2), "knight3");
	_objectManager->Add(new Knight(_objectManager, VGet(10.6f,  komaY, oneRow), player2), "knight4");
	// �⏫��ǉ�
	_objectManager->Add(new SilverGeneral(_objectManager, VGet(-7.1f, komaY, oneRow), player2), "silver3");
	_objectManager->Add(new SilverGeneral(_objectManager, VGet(7.1f,  komaY, oneRow), player2), "silver4");
	// ������ǉ�
	_objectManager->Add(new GoldGeneral(_objectManager, VGet(-3.6f, komaY, oneRow), player2), "gold3");
	_objectManager->Add(new GoldGeneral(_objectManager, VGet(3.4f,  komaY, oneRow), player2), "gold4");

	// ���ǉ�
	_objectManager->Add(new Tatami(VGet(44, -10, 15)), "tatami1");
	_objectManager->Add(new Tatami(VGet(-44, -10, 15)), "tatami2");

	return true;
}

