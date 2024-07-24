/*
 ModeGame.cpp
 概要：実際にゲームをプレイするモード
*/

#include "AppFrame.h"
#include "ApplicationMain.h"

#include "ModeGame.h"
#include "ModeEnd.h"
#include "ModeDebug.h"
#include "ModeWidget.h"

#include "ObjectManager.h"
#include "Camera.h"
#include "Light.h"
#include "ShogiBan.h"
#include "PieceStand.h"
#include "Tatami.h"

#include "Square.h"
#include "Board.h"
#include "Player.h"

bool ModeGame::Initialize()
{
	if(!base::Initialize()) return false; 

	ResourceManager::Init();
	
	JsonManeger::Init();

	// オブジェクト管理を生成
	_objectManager = new ObjectManager();
	
	// データの読み込み
	LoadData();

	// _objectManagerがnullptrの場合は強制終了する
	if(!ObjectAdd()) return false;

	// 現在のプレイヤーをplayer1に設定
	_currentPlayer = "player1";

	// 勝利フラグを初期化
	_isWin					= false;
	_isDebugCurrentPlayer	= false;

	// UIを描画する画面を追加
	ModeServer::GetInstance()->Add(new ModeWidget(_objectManager), 100, "Widget");

	return true;
}

bool ModeGame::Terminate() 
{
	base::Terminate();

	ResourceManager::Release();

	JsonManeger::Release();

	_mapChip.clear();

	// オブジェクト管理を削除
	delete _objectManager;

	return true;
}

bool ModeGame::Process() 
{
	base::Process();

	// 入力情報を取得
	auto app	= ApplicationMain::GetInstance();
	int trg		= app->GetTrg();

	// モードサーバークラスのインスタンスを取得
	auto modeServer = ModeServer::GetInstance();

	// デバッグモードに遷移
	if (trg & PAD_INPUT_10) modeServer->Add(new ModeDebug(_objectManager), 200, "debug");

	// Zキーが押されたら終了モードに遷移
	if (trg & PAD_INPUT_1 && _isWin) 
	{
		modeServer->Del(modeServer->Get("Widget"));
		modeServer->Del(this);
		modeServer->Add(new ModeEnd(),1,"end");
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

	// 現在のプレイヤーを表示
	std::string currentPlayer = "現在のプレイヤー: " + _currentPlayer;
	DrawFormatString(0, 20, GetColor(255, 255, 255), currentPlayer.c_str());

	if (_isWin) 
	{
		std::string winner = _strWinPlayer + "の勝利! \n次に進むにはBボタンを押してください";
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
	ResourceManager::MV1LoadModel("res/3D/将棋盤/sho_giban.mv1");
	ResourceManager::MV1LoadModel("res/3D/将棋の駒台.mv1");
	ResourceManager::MV1LoadModel("res/3D/tatami/ImageToStl.com_772_tatami.mv1");
}

bool ModeGame::ObjectAdd()
{
	if(!_objectManager) return false;

	// カメラを追加
	_objectManager->Add(new Camera(), "Camera");

	// ライトを追加
	_objectManager->Add(new Light(), "light");

	// 将棋盤を追加
	_objectManager->Add(new ShogiBan(), "shogiban");

	// ボードを追加
	_objectManager->Add(new Board(_objectManager), "board");
	
	// 駒台を追加
	_objectManager->Add(new PieceStand(_objectManager, VGet(24, 0, -10), "player2"), "PieceStand2");
	_objectManager->Add(new PieceStand(_objectManager, VGet(-24, 0, -10), "player1"), "PieceStand1");

	// 畳を追加
	_objectManager->Add(new Tatami(VGet(44, -10, 15)), "tatami1");
	_objectManager->Add(new Tatami(VGet(-44, -10, 15)), "tatami2");

	// プレイヤーを追加
	_objectManager->Add(new Player(_objectManager, "player1", this), "player1");
	_objectManager->Add(new Player(_objectManager, "player2", this), "player2");

	return true;
}

void ModeGame::ChangeCurrentPlayer()
{
	// デバッグモードの場合はplayer1に強制的に変更
	if (_isDebugCurrentPlayer)
	{
		_currentPlayer = "player1"; return;
	}

	// 現在のプレイヤーを変更
	_currentPlayer = _currentPlayer == "player1" ? "player2" : "player1";
}


