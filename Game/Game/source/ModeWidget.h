#pragma once

#include "appframe.h"
#include "ObjectManager.h"
#include "WidgetManager.h"

class ModeWidget : public ModeBase
{
	typedef ModeBase base;
public:
	ModeWidget(ObjectManager* objManager);
	~ModeWidget();

	bool Initialize()	override;
	bool Terminate()	override;
	bool Process()		override;
	bool Render()		override;

private:
	ObjectManager* _objManager;
	std::unique_ptr<WidgetManager> _ptrWidgetManager;
};

