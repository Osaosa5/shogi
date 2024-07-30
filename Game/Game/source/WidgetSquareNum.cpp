
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
		// ���[���h���W����X�N���[�����W�ɕϊ�
		VECTOR pos = ConvWorldPosToScreenPos(square->GetCenterPos());

		// �X�N���[�����W��FullHD���W�ɕϊ�
		//VECTOR fullHDPos = ConvertPosToFullHD(pos, dispW, dispH);

		DrawFormatString(pos.x, pos.y, GetColor(255, 255, 255), "%d", num);
		num++;
	}

	return true;
}
