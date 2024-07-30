
#include "WidgetSquareNum.h"

#include "Board.h"
#include "ApplicationMain.h"

WidgetSquareNum::WidgetSquareNum(ObjectManager* ptrObjManager)
	: Widget(ptrObjManager)
{}

WidgetSquareNum::~WidgetSquareNum()
{
}

bool WidgetSquareNum::Initialize()
{
	return true;
}

bool WidgetSquareNum::Terminate()
{
	return true;
}

bool WidgetSquareNum::Process()
{
	return true;
}

bool WidgetSquareNum::Render()
{
	auto ptrBoard = dynamic_cast<Board*>(_ptrObjManager->Get("board"));
	auto vSquares = ptrBoard->GetSquares();

	auto ptrApp = ApplicationMain::GetInstance();

	float dispW = ptrApp->DispSizeW();
	float dispH = ptrApp->DispSizeH();

	int num = 0;
	for (auto& square : vSquares)
	{
		// ワールド座標からスクリーン座標に変換
		VECTOR pos = ConvWorldPosToScreenPos(square->GetCenterPos());

		// スクリーン座標をFullHD座標に変換
		//VECTOR fullHDPos = ConvertPosToFullHD(pos, dispW, dispH);

		DrawFormatString(pos.x, pos.y, GetColor(255, 255, 255), "%d", num);
		num++;
	}

	return true;
}
