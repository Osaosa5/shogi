#pragma once

#include "appframe.h"

#include "ObjectManager.h"

class ModeDebug : public ModeBase
{
	typedef ModeBase base;
public:
	ModeDebug(ObjectManager* objManager);
	~ModeDebug();

	bool Initialize()	override;
	bool Terminate()	override;
	bool Process()		override;
	bool Render()		override;

	float ConvertXPosToDispSize(float pos, float dispW);
	float ConvertYPosToDispSize(float pos, float dispH);

private:
	ObjectManager* _objManager;

	struct DEBUG_MENU 
	{
		std::string name;
		bool		isSelect;

		std::function<void(ObjectManager* objManager)>	objFunc;
	};
	std::vector<DEBUG_MENU> _debugItems;

	int _selectIndex;
};


