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

bool ModeGame::Initialize()
{
	if (!base::Initialize()) { return false; }

	ResourceManager::Init();

	// オブジェクト管理を生成
	_objectManager = new ObjectManager();
	// カメラを追加
	_objectManager->Add(new Camera(),"camera");
	// ライトを追加
	_objectManager->Add(new Light(), "light");
	// 将棋盤を追加
	_objectManager->Add(new ShogiBan(), "shogiban");
	// 歩兵を追加
	_objectManager->Add(new Fuhyo(_objectManager), "fuhyo1");
	// 畳を追加
	_objectManager->Add(new Tatami(VGet(44,-10,15)), "tatami1");
	_objectManager->Add(new Tatami(VGet(-44, -10, 15)), "tatami2");

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

