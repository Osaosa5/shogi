#pragma once

#include "appframe.h"
#include "Widget.h"
#include "Shogi.h"

constexpr int PIECE_NUM = 7;
constexpr int STAND_NUM = 2;


class WidgetPieceNumber : public Widget
{
	using PIECE = Shogi::PIECE_TYPE;
	using PieceNums = std::map<PIECE, int>;
public:
	WidgetPieceNumber(ObjectManager* ptrObjManager);
	~WidgetPieceNumber();

	bool Initialize()	override;
	bool Terminate()	override;
	bool Process()		override;
	bool Render()		override;

private:
	std::map<std::string, PieceNums> _mPieceNums;
};

