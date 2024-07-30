
#include "appframe.h"
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
	BUTTON debugCamera;
	debugCamera.name		= "DebugCamera";
	debugCamera.isSelect	= false;
	debugCamera.objFunc		= [](ObjectManager* objManager) 
		{
			auto camera = dynamic_cast<Camera*>(objManager->Get("Camera"));
			camera->SetIsDebugCamera(true);
		};
	_debugItems.emplace_back(debugCamera);

	BUTTON doNotChangeTurn;
	doNotChangeTurn.name		= "DoNotChangeTurn";
	doNotChangeTurn.isSelect	= false;
	doNotChangeTurn.objFunc		= [](ObjectManager* objManager)
		{
			auto game = dynamic_cast<ModeGame*>(ModeServer::GetInstance()->Get("Game"));
			game->SetDebugCurrentPlayer(!game->IsDebugCurrentPlayer());
		};	
	_debugItems.emplace_back(doNotChangeTurn);

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

	VECTOR boxPos = ConvertPosToFullHD(VGet(300,100,0), dispW, dispH);
	DrawBox(0, 0, boxPos.x, boxPos.y, GetColor(0, 0, 0), TRUE);

	VECTOR lineFeed = ConvertPosToFullHD(VGet(0, 20, 0), dispW, dispH);
	float y = 0;
	int index = 0;
	for (auto& item : _debugItems)
	{
		if(index == _selectIndex) 
		{
			int strLength	= item.name.length();
			VECTOR pos		= ConvertPosToFullHD(VGet((strLength + 1) * 16, y, 0), dispW, dispH);
			float x			= ConvertXPosToDispSize((strLength + 1) * 16, dispW);
			DrawString(pos.x, pos.y, "<-", GetColor(255, 0, 0));
		}
		DrawFormatString(0, y, GetColor(255, 255, 255), item.name.c_str());
		y += lineFeed.y;
		index++;
	}

	return true;
}
