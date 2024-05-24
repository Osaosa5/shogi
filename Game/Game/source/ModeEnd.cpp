/*
 ModeEnd.cpp
 作成日：2024/05/21
 編集日：2024/05/21
 概要：ゲーム終了後の画面を表示するモード
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

	// 入力情報を取得
	auto app = ApplicationMain::GetInstance();
	int trg = app->GetTrg();

	// Zキーが押されたらタイトルに戻る
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

	// モード名を表示
	std::string name = ModeServer::GetInstance()->GetName(this);
	DrawFormatString(0, 0, GetColor(255, 255, 255), name.c_str());

	return true;
}
