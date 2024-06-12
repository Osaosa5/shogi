/*
 ModeGame.cpp
 作成日：2024/05/21
 編集日：2024/05/21
 概要：実際にゲームをプレイするモード
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
	
	// オブジェクト管理を生成
	_objectManager = new ObjectManager();
	
	// _objectManagerがnullptrの場合は強制終了する
	if(!ObjectAdd()) return false;

	return true;
}

bool ModeGame::Terminate() 
{
	base::Terminate();

	ResourceManager::Release();

	// オブジェクト管理を削除
	delete _objectManager;

	return true;
}

bool ModeGame::Process() 
{
	base::Process();

	// 入力情報を取得
	auto app = ApplicationMain::GetInstance();
	int trg = app->GetTrg();

	// Zキーが押されたら終了モードに遷移
	if (trg & PAD_INPUT_1) {
		auto mdServer = ModeServer::GetInstance();
		mdServer->Del(this);
		mdServer->Add(new ModeEnd(),1,"end");
	}

	// オブジェクトを更新
	_objectManager->Process();

	return true;
}

bool ModeGame::Render() 
{
	base::Render();

	// Ｚバッファを有効にする
	SetUseZBuffer3D(TRUE);

	// Ｚバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);

	// オブジェクトを描画
	_objectManager->Render();

	// モード名を表示
	std::string name = ModeServer::GetInstance()->GetName(this);
	DrawFormatString(0, 0, GetColor(255, 255, 255), name.c_str());

	return true;
}

bool ModeGame::ObjectAdd()
{
	if(!_objectManager) return false;

	// カメラを追加
	_objectManager->Add(new Camera(), "camera");
	// ライトを追加
	_objectManager->Add(new Light(), "light");
	// 将棋盤を追加
	_objectManager->Add(new ShogiBan(), "shogiban");

	// 駒のY座標
	float komaY = 21.0f;
	// player1の駒
	auto player1 = Shogi::PLAYER_TYPE::kPlayer1;
	// 歩兵を追加
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
	// 香車を追加
	float nineRow = -15.4f;
	_objectManager->Add(new Lance(_objectManager, VGet(-14.3f, komaY, nineRow), player1), "lance1");
	_objectManager->Add(new Lance(_objectManager, VGet(14.2f,  komaY, nineRow), player1), "lance2");
	// 桂馬を追加
	_objectManager->Add(new Knight(_objectManager, VGet(-10.6f, komaY, nineRow), player1), "knight1");
	_objectManager->Add(new Knight(_objectManager, VGet(10.6f,  komaY, nineRow), player1), "knight2");
	// 銀将を追加
	_objectManager->Add(new SilverGeneral(_objectManager, VGet(-7.1f, komaY, nineRow), player1), "silver1");
	_objectManager->Add(new SilverGeneral(_objectManager, VGet(7.1f,  komaY, nineRow), player1), "silver2");
	// 金将を追加
	_objectManager->Add(new GoldGeneral(_objectManager, VGet(-3.6f, komaY, nineRow), player1), "gold1");
	_objectManager->Add(new GoldGeneral(_objectManager, VGet(3.4f,  komaY, nineRow), player1), "gold2");

	// player2の駒
	auto player2 = Shogi::PLAYER_TYPE::kPlayer2;
	// 歩兵を追加
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
	// 香車を追加
	float oneRow = 15.7f;
	_objectManager->Add(new Lance(_objectManager, VGet(-14.3f, komaY, oneRow), player2), "lance3");
	_objectManager->Add(new Lance(_objectManager, VGet(14.2f,  komaY, oneRow), player2), "lance4");
	// 桂馬を追加
	_objectManager->Add(new Knight(_objectManager, VGet(-10.6f, komaY, oneRow), player2), "knight3");
	_objectManager->Add(new Knight(_objectManager, VGet(10.6f,  komaY, oneRow), player2), "knight4");
	// 銀将を追加
	_objectManager->Add(new SilverGeneral(_objectManager, VGet(-7.1f, komaY, oneRow), player2), "silver3");
	_objectManager->Add(new SilverGeneral(_objectManager, VGet(7.1f,  komaY, oneRow), player2), "silver4");
	// 金将を追加
	_objectManager->Add(new GoldGeneral(_objectManager, VGet(-3.6f, komaY, oneRow), player2), "gold3");
	_objectManager->Add(new GoldGeneral(_objectManager, VGet(3.4f,  komaY, oneRow), player2), "gold4");

	// 畳を追加
	_objectManager->Add(new Tatami(VGet(44, -10, 15)), "tatami1");
	_objectManager->Add(new Tatami(VGet(-44, -10, 15)), "tatami2");

	return true;
}

