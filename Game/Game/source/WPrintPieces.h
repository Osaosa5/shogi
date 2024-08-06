#pragma once

#include "Widget.h"

class WPrintPieces : public Widget
{
	public:
	WPrintPieces(ObjectManager* ptrObjManager);
	~WPrintPieces();

	bool Initialize() override;
	bool Terminate() override;
	bool Process() override;
	bool Render() override;
};

