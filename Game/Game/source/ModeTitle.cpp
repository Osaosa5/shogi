/*
 ModeTitle.cpp
 作成日：2024/05/21
 編集日：2024/05/21
 概要：タイトル画面を表示するモード
*/

#include "AppFrame.h"
#include "ApplicationMain.h"

#include "ModeTitle.h"
#include "ModeGame.h"

#include <iostream>

bool ModeTitle::Initialize()
{
	if (!base::Initialize()) { return false; }
	return true;
}

bool ModeTitle::Terminate()
{
	base::Terminate();
	return true;
}

bool ModeTitle::Process()
{
	base::Process();

	// 入力情報を取得
	auto app = ApplicationMain::GetInstance();
	int trg = app->GetTrg();

	// Zキーが押されたらゲームモードに遷移
	if (trg & PAD_INPUT_1) {
		auto mdServer = ModeServer::GetInstance();
		mdServer->Del(this);
		mdServer->Add(new ModeGame(), 1, "Game");
	}

	return true;
}

bool ModeTitle::Render()
{
	base::Render();

	// モード名を表示
	auto app = ApplicationMain::GetInstance();
	float wid = app->DispSizeW(); float hei = app->DispSizeH();
	std::string name = "将棋";
	float size = GetFontSize();
	SetFontSize(128);
	DrawFormatString(wid / 2 - 156, hei / 2 - 128, GetColor(255, 255, 255), name.c_str());
	SetFontSize(size);

	return true;
}
