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

	struct BUTTON 
	{
		std::string name;
		bool		isSelect;
		std::function<void(ObjectManager* ptrObjManager)>	objFunc;
	};
	std::vector<BUTTON> _debugItems;

	int _selectIndex;
};


