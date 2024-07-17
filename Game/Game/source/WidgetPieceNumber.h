#pragma once

#include "Widget.h"

class WidgetPieceNumber : public Widget
{
public:
	WidgetPieceNumber(ObjectManager* ptrObjManager);
	~WidgetPieceNumber();

	bool Initialize()	override;
	bool Terminate()	override;
	bool Process()		override;
	bool Render()		override;

private:

};

