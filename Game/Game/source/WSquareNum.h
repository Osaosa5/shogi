#pragma once

#include "appframe.h"

#include "Widget.h"
#include "ObjectManager.h"

class WSquareNum :  public Widget
{
public:
	WSquareNum(ObjectManager* ptrObjManager);
	~WSquareNum();

	bool Initialize() override;
	bool Terminate() override;
	bool Process() override;
	bool Render() override;

private:
};

