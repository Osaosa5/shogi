#pragma once

#include "appframe.h"
#include "Widget.h"
#include "Shogi.h"

constexpr int STAND_NUM = 2;

class WPieceNumber : public Widget
{
	using PIECE		= Shogi::PIECE_TYPE;
	using PieceNums = std::unordered_map<PIECE, int>;
public:
	WPieceNumber(ObjectManager* ptrObjManager);
	~WPieceNumber();

	bool Initialize()	override;
	bool Terminate()	override;
	bool Process()		override;
	bool Render()		override;

private:
	std::unordered_map<std::string, PieceNums> _mPieceNums;

	
};

