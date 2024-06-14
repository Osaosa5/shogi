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
	
	JSONFile JSON("JSON/board.json");
	_mapChip = JSON.Data()["map"].get<std::vector<int>>();

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

	// �}�X��ǉ�
	for(int y = 0; y < 9; y++) {
		for(int x = 0; x < 9; x++) {
			// �}�X��x������3.5f�Az������3.85f�����炵�Ĕz�u
			float w = 3.53f; float h = 3.87f;
			VECTOR pos = VGet(-15.88f + w * x, 21, 13.55f - h * y);
			std::pair<float, float> size = std::make_pair(w - 0.01f, h - 0.01f);

			// �}�X�̃}�b�v�`�b�v���擾
			int mapChip = _mapChip[y * 9 + x];

			// �}�X�̐w�n���ǂ���̃v���C���[�̂��̂����擾
			// 0~2�s�ڂ�player2�A3~5�s�ڂ͒����A6~8�s�ڂ�player1
			std::string player;
			if(y < 3) player = "player2";
			else if(y > 5) player = "player1";
			else player = "";

			std::string name = "square" + std::to_string(x + y * 9);
			_objectManager->Add(new Square(pos, size, mapChip, player), name.c_str());
		}
	}


	// ���Y���W
	float komaY = 21.0f;
	// player1�ɕK�v�ȋ���
	auto player1 = Shogi::PLAYER_TYPE::kPlayer1;
	float sevenRow = -7.70f; float eightRow = -11.55f; float nineRow = -15.40f;
	// player2�ɕK�v�ȋ���
	auto player2 = Shogi::PLAYER_TYPE::kPlayer2;
	float oneRow = 15.40f; float twoRow = 11.55f; float threeRow = 7.70f;

	// ���ǉ�
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

	// ���ǉ�
	_objectManager->Add(new Tatami(VGet(44, -10, 15)), "tatami1");
	_objectManager->Add(new Tatami(VGet(-44, -10, 15)), "tatami2");

	return true;
}

