
#include "ModeWidget.h"

#include "WPieceNumber.h"
#include "WSquareNum.h"
#include "WPrintPieces.h"

ModeWidget::ModeWidget(ObjectManager* objManager)
{
	_objManager = objManager;
}

ModeWidget::~ModeWidget()
{
}

bool ModeWidget::Initialize()
{
	if (!base::Initialize()) return false;

	_ptrWidgetManager = std::make_unique<WidgetManager>();

	_ptrWidgetManager->Add(new WPieceNumber(_objManager), "PieceNumber");

#ifdef ON_DEBUG
	_ptrWidgetManager->Add(new WSquareNum(_objManager), "SquareNum");
	_ptrWidgetManager->Add(new WPrintPieces(_objManager), "PrintPieces");
#endif

	_ptrWidgetManager->Initialize();

	return true;
}

bool ModeWidget::Terminate()
{
	base::Terminate();

	_ptrWidgetManager->Terminate();

	return true;
}

bool ModeWidget::Process()
{
	base::Process();

	_ptrWidgetManager->Process();

	return true;
}

bool ModeWidget::Render()
{
	base::Render();

	_ptrWidgetManager->Render();

	return true;
}
