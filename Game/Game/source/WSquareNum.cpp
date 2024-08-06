
#include "WSquareNum.h"

#include "Board.h"
#include "ApplicationMain.h"

WSquareNum::WSquareNum(ObjectManager* ptrObjManager)
	: Widget(ptrObjManager)
{}

WSquareNum::~WSquareNum()
{
}

bool WSquareNum::Initialize()
{
	return true;
}

bool WSquareNum::Terminate()
{
	return true;
}

bool WSquareNum::Process()
{
	return true;
}

bool WSquareNum::Render()
{
	auto ptrBoard = dynamic_cast<Board*>(_ptrObjManager->Get("board"));
	auto vSquares = ptrBoard->GetSquares();

	int num = 0;
	for (auto& square : vSquares)
	{
		// ワールド座標からスクリーン座標に変換
		VECTOR pos = ConvWorldPosToScreenPos(square->GetCenterPos());
		pos.y -= 10;
		DrawFormatString(pos.x, pos.y, GetColor(255, 255, 255), "%d", num);
		num++;
	}

	return true;
}
