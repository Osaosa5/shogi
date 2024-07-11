/*
 ModeGame.cpp
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

#include "Square.h"
#include "Board.h"
#include "Player.h"

bool ModeGame::Initialize()
{
	if(!base::Initialize()) return false; 

	ResourceManager::Init();
	
	JsonManeger::Init();

	// �I�u�W�F�N�g�Ǘ��𐶐�
	_objectManager = new ObjectManager();
	
	// �f�[�^�̓ǂݍ���
	LoadData();

	// _objectManager��nullptr�̏ꍇ�͋����I������
	if(!ObjectAdd()) return false;

	// ���݂̃v���C���[��player1�ɐݒ�
	_currentPlayer = "player1";

	// �����t���O��������
	_isWin = false;

	return true;
}

bool ModeGame::Terminate() 
{
	base::Terminate();

	ResourceManager::Release();

	JsonManeger::Release();

	_mapChip.clear();

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
	if (trg & PAD_INPUT_1 && _isWin) {
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

	// ���݂̃v���C���[��\��
	std::string currentPlayer = "���݂̃v���C���[: " + _currentPlayer;
	DrawFormatString(0, 20, GetColor(255, 255, 255), currentPlayer.c_str());

	if (_isWin) {
		std::string winner = _strWinPlayer + "�̏���! \n���ɐi�ނɂ�B�{�^���������Ă�������";
		int fontSize = GetFontSize();
		SetFontSize(64);
		DrawFormatString(0, 20, GetColor(255, 0, 0), winner.c_str());
		SetFontSize(fontSize);
	}

	return true;
}

void ModeGame::LoadData()
{
	JsonManeger::LoadJsonFile("JSON/board.json");
	ResourceManager::MV1LoadModel("res/3D/shogi/kaku.mv1");
	ResourceManager::MV1LoadModel("res/3D/shogi/fuhyo.mv1");
	ResourceManager::MV1LoadModel("res/3D/shogi/kin.mv1");
	ResourceManager::MV1LoadModel("res/3D/shogi/oh.mv1");
	ResourceManager::MV1LoadModel("res/3D/shogi/gyoku.mv1");
	ResourceManager::MV1LoadModel("res/3D/shogi/keima.mv1");
	ResourceManager::MV1LoadModel("res/3D/shogi/kyousha.mv1");
	ResourceManager::MV1LoadModel("res/3D/shogi/hisha.mv1");
	ResourceManager::MV1LoadModel("res/3D/shogi/gin.mv1");
	ResourceManager::MV1LoadModel("res/3D/������/sho_giban.mv1");
	ResourceManager::MV1LoadModel("res/3D/tatami/ImageToStl.com_772_tatami.mv1");
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

	// �{�[�h��ǉ�
	_objectManager->Add(new Board(_objectManager), "board");
	
	// ���ǉ�
	_objectManager->Add(new Tatami(VGet(44, -10, 15)), "tatami1");
	_objectManager->Add(new Tatami(VGet(-44, -10, 15)), "tatami2");

	// �v���C���[��ǉ�
	_objectManager->Add(new Player(_objectManager, "player1", this), "player1");
	_objectManager->Add(new Player(_objectManager, "player2", this), "player2");

	return true;
}

