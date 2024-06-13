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

#include "Fuhyo.h"
#include "Lance.h"
#include "Knight.h"
#include "SilverGeneral.h"
#include "GoldGeneral.h"
#include "King.h"
#include "Bishop.h"
#include "Rook.h"

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

	for(int i = 0; i < 9; i++) {
		float z = 3.85f * i - 15.4f;
		VECTOR WorldPos = VGet(-50, 21, z);
		DrawLine3D(WorldPos, VGet(50, 21, z), GetColor(255, 0, 0));
		VECTOR localPos = ConvWorldPosToScreenPos(WorldPos);
		DrawFormatString(0, localPos.y, GetColor(255, 255, 255), "%3.2f", z);
	}

	for(int i = 0; i < 9; i++) {
		float x = 3.5f * i - 14.0f;
		VECTOR WorldPos = VGet(x, 21, 50);
		DrawLine3D(WorldPos, VGet(x, 21, -50), GetColor(255, 0, 0));
		VECTOR localPos = ConvWorldPosToScreenPos(WorldPos);
		DrawFormatString(localPos.x * 2 - 650, 300, GetColor(255, 255, 255), "%3.2f", x);
	}

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

	// player1�ɕK�v�ȋ��ǉ�
	auto player1 = Shogi::PLAYER_TYPE::kPlayer1;
	float sevenRow = -7.70f; float eightRow = -11.55f; float nineRow = -15.40f;
	// player2�ɕK�v�ȋ��ǉ�
	auto player2 = Shogi::PLAYER_TYPE::kPlayer2;
	float oneRow = 15.40f; float twoRow = 11.55f; float threeRow = 7.70f;

	for (int i = 0; i < 9; i++) {
		float x = 3.5f * i - 14.0f;
		std::string fuhyoPl1 = "fuhyo" + std::to_string(i + 1);
		std::string fuhyoPl2 = "fuhyo" + std::to_string(i + 10);
		_objectManager->Add(new Fuhyo(_objectManager, VGet(x, komaY, sevenRow), player1), fuhyoPl1.c_str());
		_objectManager->Add(new Fuhyo(_objectManager, VGet(x, komaY, threeRow), player2), fuhyoPl2.c_str());
		if (i == 0) {
			_objectManager->Add(new Lance(_objectManager, VGet(x, komaY, nineRow), player1), "lance1");
			_objectManager->Add(new Lance(_objectManager, VGet(x, komaY, oneRow), player2), "lance2");
		}
		else if (i == 1) {
			_objectManager->Add(new Bishop(_objectManager, VGet(x, komaY, eightRow), player1), "bishop1");
			_objectManager->Add(new Rook(_objectManager, VGet(x, komaY, twoRow), player2), "rook1");
			_objectManager->Add(new Knight(_objectManager, VGet(x, komaY, nineRow), player1), "knight1");
			_objectManager->Add(new Knight(_objectManager, VGet(x, komaY, oneRow), player2), "knight2");
		}
		else if (i == 2) {
			_objectManager->Add(new SilverGeneral(_objectManager, VGet(x, komaY, nineRow), player1), "silver1");
			_objectManager->Add(new SilverGeneral(_objectManager, VGet(x, komaY, oneRow), player2), "silver2");
		}
		else if (i == 3) {
			_objectManager->Add(new GoldGeneral(_objectManager, VGet(x, komaY, nineRow), player1), "gold1");
			_objectManager->Add(new GoldGeneral(_objectManager, VGet(x, komaY, oneRow), player2), "gold2");
		}
		else if (i == 4) {
			_objectManager->Add(new King(_objectManager, VGet(x, komaY, nineRow), player1), "king1");
			_objectManager->Add(new King(_objectManager, VGet(x, komaY, oneRow), player2), "king2");
		}
		else if (i == 5) {
			_objectManager->Add(new GoldGeneral(_objectManager, VGet(x, komaY, nineRow), player1), "gold3");
			_objectManager->Add(new GoldGeneral(_objectManager, VGet(x, komaY, oneRow), player2), "gold4");
		}
		else if (i == 6) {
			_objectManager->Add(new SilverGeneral(_objectManager, VGet(x, komaY, nineRow), player1), "silver3");
			_objectManager->Add(new SilverGeneral(_objectManager, VGet(x, komaY, oneRow), player2), "silver4");
		}
		else if (i == 7) {
			_objectManager->Add(new Rook(_objectManager, VGet(x, komaY, eightRow), player1), "rook2");
			_objectManager->Add(new Bishop(_objectManager, VGet(x, komaY, twoRow), player2), "bishop2");
			_objectManager->Add(new Knight(_objectManager, VGet(x, komaY, nineRow), player1), "knight3");
			_objectManager->Add(new Knight(_objectManager, VGet(x, komaY, oneRow), player2), "knight4");
		}
		else if (i == 8) {
			_objectManager->Add(new Lance(_objectManager, VGet(x, komaY, nineRow), player1), "lance3");
			_objectManager->Add(new Lance(_objectManager, VGet(x, komaY, oneRow), player2), "lance4");
		}
	}

	// player2�̋�
	// ������ǉ�
	

	//_objectManager->Add(new Fuhyo(_objectManager, VGet(-14.3f, komaY, threeRow), player2), "fuhyo10");
	//_objectManager->Add(new Fuhyo(_objectManager, VGet(-10.6f, komaY, threeRow), player2), "fuhyo11");
	//_objectManager->Add(new Fuhyo(_objectManager, VGet(-7.1f,  komaY, threeRow), player2), "fuhyo12");
	//_objectManager->Add(new Fuhyo(_objectManager, VGet(-3.6f,  komaY, threeRow), player2), "fuhyo13");
	//_objectManager->Add(new Fuhyo(_objectManager, VGet(-0.1f,  komaY, threeRow), player2), "fuhyo14");
	//_objectManager->Add(new Fuhyo(_objectManager, VGet(3.4f,   komaY, threeRow), player2), "fuhyo15");
	//_objectManager->Add(new Fuhyo(_objectManager, VGet(7.1f,   komaY, threeRow), player2), "fuhyo16");
	//_objectManager->Add(new Fuhyo(_objectManager, VGet(10.6f,  komaY, threeRow), player2), "fuhyo17");
	//_objectManager->Add(new Fuhyo(_objectManager, VGet(14.2f,  komaY, threeRow), player2), "fuhyo18");
	//
	//// �p�s��ǉ�
	//_objectManager->Add(new Bishop(_objectManager, VGet(10.6f, komaY, twoRow), player2), "bishop2");
	//// ��Ԃ�ǉ�
	//_objectManager->Add(new Rook(_objectManager, VGet(-10.6f, komaY, twoRow), player2), "rook2");
	//
	//// ���Ԃ�ǉ�
	//_objectManager->Add(new Lance(_objectManager, VGet(-14.3f, komaY, oneRow), player2), "lance3");
	//_objectManager->Add(new Lance(_objectManager, VGet(14.2f,  komaY, oneRow), player2), "lance4");
	//// �j�n��ǉ�
	//_objectManager->Add(new Knight(_objectManager, VGet(-10.6f, komaY, oneRow), player2), "knight3");
	//_objectManager->Add(new Knight(_objectManager, VGet(10.6f,  komaY, oneRow), player2), "knight4");
	//// �⏫��ǉ�
	//_objectManager->Add(new SilverGeneral(_objectManager, VGet(-7.1f, komaY, oneRow), player2), "silver3");
	//_objectManager->Add(new SilverGeneral(_objectManager, VGet(7.1f,  komaY, oneRow), player2), "silver4");
	//// ������ǉ�
	//_objectManager->Add(new GoldGeneral(_objectManager, VGet(-3.6f, komaY, oneRow), player2), "gold3");
	//_objectManager->Add(new GoldGeneral(_objectManager, VGet(3.4f,  komaY, oneRow), player2), "gold4");
	//// ������ǉ�
	//_objectManager->Add(new King(_objectManager, VGet(-0.1f, komaY, oneRow), player2), "king2");

	// ���ǉ�
	_objectManager->Add(new Tatami(VGet(44, -10, 15)), "tatami1");
	_objectManager->Add(new Tatami(VGet(-44, -10, 15)), "tatami2");

	return true;
}

