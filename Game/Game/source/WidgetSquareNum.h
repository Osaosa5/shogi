#pragma once

#include "appframe.h"

#include "Widget.h"
#include "ObjectManager.h"

class WidgetSquareNum :  public Widget
{
public:
	WidgetSquareNum(ObjectManager* ptrObjManager);
	~WidgetSquareNum();

	bool Initialize() override;
	bool Terminate() override;
	bool Process() override;
	bool Render() override;

private:
};

