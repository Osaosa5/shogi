
#include "WidgetPieceNumber.h"
#include "PieceStand.h"

WidgetPieceNumber::WidgetPieceNumber(ObjectManager* ptrObjManager)
	: Widget(ptrObjManager)
{
}

WidgetPieceNumber::~WidgetPieceNumber()
{
}

bool WidgetPieceNumber::Initialize()
{
	return true;
}

bool WidgetPieceNumber::Terminate()
{
	return true;
}

bool WidgetPieceNumber::Process()
{
	// オブジェクトマネージャーから駒台を取得する
	auto pieceStand_1 = dynamic_cast<PieceStand*>(_ptrObjManager->Get("PieceStand1"));
	auto pieceStand_2 = dynamic_cast<PieceStand*>(_ptrObjManager->Get("PieceStand2"));
	
	// 駒台の駒数を取得する


	return true;
}

bool WidgetPieceNumber::Render()
{
	int fontSize = GetFontSize();
	SetFontSize(20);
	DrawString(0, 0, "PieceNumber", GetColor(255, 255, 255));
	SetFontSize(fontSize);
	return true;
}
