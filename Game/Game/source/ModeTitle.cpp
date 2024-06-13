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
	nlohmann::json j;
	JSONFile json("JSON/board.json");
	if (json.Success()) {
		j = json.Data();
	}
	else {
		return false;
	}

	_vMap = j["map"].get<std::vector<int>>();

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
		mdServer->Add(new ModeGame(), 1, "game");
	}

	return true;
}

bool ModeTitle::Render()
{
	base::Render();

	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			int num = _vMap[y * 9 + x];
			if(x == 8) DrawFormatString(x * 32, y * 32, GetColor(255, 255, 255), "%d\n", _vMap[y * 9 + x]);
			else DrawFormatString(x * 32, y * 32, GetColor(255, 255, 255), "%d", _vMap[y * 9 + x]);
		}
	}


	// モード名を表示
	/*std::string name = ModeServer::GetInstance()->GetName(this);
	DrawFormatString(0, 0, GetColor(255, 255, 255), name.c_str());*/

	return true;
}
