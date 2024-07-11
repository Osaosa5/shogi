#pragma once

#include "appframe.h"

#include "ObjectManager.h"

class ModeDebug : public ModeBase
{
	typedef ModeBase base;
public:
	ModeDebug(ObjectManager* objManager);
	~ModeDebug() = 0;

	bool Initialize()override;
	bool Terminate()override;
	bool Process()override;
	bool Render()override;

private:
	ObjectManager* _objManager;
};

