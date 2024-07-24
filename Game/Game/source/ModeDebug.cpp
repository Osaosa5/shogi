
#include "ModeDebug.h"
#include "ApplicationMain.h"
#include "Camera.h"
#include "ModeGame.h"

ModeDebug::ModeDebug(ObjectManager* objManager)
{
	_objManager = objManager;
}

ModeDebug::~ModeDebug()
{
}

bool ModeDebug::Initialize()
{
	DEBUG_MENU debugCamera;
	debugCamera.name		= "DebugCamera";
	debugCamera.isSelect	= false;
	debugCamera.objFunc		= [](ObjectManager* objManager) 
		{
			auto camera = dynamic_cast<Camera*>(objManager->Get("Camera"));
			camera->SetIsDebugCamera(true);
		};
	_debugItems.emplace_back(debugCamera);

	DEBUG_MENU DoNotChangeTurn;
	DoNotChangeTurn.name		= "DoNotChangeTurn";
	DoNotChangeTurn.isSelect	= false;
	DoNotChangeTurn.objFunc		= [](ObjectManager* objManager)
		{
			auto game = dynamic_cast<ModeGame*>(ModeServer::GetInstance()->Get("Game"));
			game->SetDebugCurrentPlayer(!game->IsDebugCurrentPlayer());
		};
	_debugItems.emplace_back(DoNotChangeTurn);

	_selectIndex = 0;

	return true;
}

bool ModeDebug::Terminate()
{
	_debugItems.clear();
	return true;
}

bool ModeDebug::Process()
{
	auto modeServer = ModeServer::GetInstance();
	modeServer->SkipProcessUnderLayer();

	auto	app		= ApplicationMain::GetInstance();
	int		trg		= app->GetTrg();

	_selectIndex = SelectFocus(trg, "y", _debugItems.size(), _selectIndex);

	if (trg & PAD_INPUT_1) 
	{
		_debugItems[_selectIndex].isSelect = true;
		_debugItems[_selectIndex].objFunc(_objManager);
	}

	for (auto& item : _debugItems) 
	{
		if (item.isSelect) 
		{
			modeServer->Del(this);
		}
	}

	return true;
}

float ModeDebug::ConvertXPosToDispSize(float pos, float dispW)
{
	return dispW * pos / 1920;
}

float ModeDebug::ConvertYPosToDispSize(float pos, float dispH)
{
	return dispH * pos / 1080;
}

bool ModeDebug::Render()
{
	auto app = ApplicationMain::GetInstance();
	float dispW = app->DispSizeW();
	float dispH = app->DispSizeH();

	float boxW = ConvertXPosToDispSize(200, dispW);
	float boxH = ConvertYPosToDispSize(100, dispH);
	DrawBox(0, 0, boxW, boxH, GetColor(0, 0, 0), TRUE);

	float linefeed = ConvertYPosToDispSize(20, dispH);
	float y = 0;
	int index = 0;
	for (auto& item : _debugItems) {
		if(index == _selectIndex) {
			int strLength = item.name.length();
			float x = ConvertXPosToDispSize((strLength + 1) * 16, dispW);
			DrawString(x, y, "<-", GetColor(255, 0, 0));
		}
		DrawFormatString(0, y, GetColor(255, 255, 255), item.name.c_str());
		y += linefeed;
		index++;
	}

	return true;
}
