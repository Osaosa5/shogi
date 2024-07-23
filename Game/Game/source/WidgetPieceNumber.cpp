
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
	// �I�u�W�F�N�g�}�l�[�W���[��������擾����
	auto pieceStand_1 = dynamic_cast<PieceStand*>(_ptrObjManager->Get("PieceStand1"));
	auto pieceStand_2 = dynamic_cast<PieceStand*>(_ptrObjManager->Get("PieceStand2"));
	
	// ���̋���擾����


	return true;
}

bool WidgetPieceNumber::Render()
{
	int fontSize = GetFontSize();
	SetFontSize(20);
	DrawString(100, 0, "PieceNumber", GetColor(255, 0, 0));
	SetFontSize(fontSize);
	return true;
}
