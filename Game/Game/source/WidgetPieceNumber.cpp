
#include "WidgetPieceNumber.h"
#include "PieceStand.h"

WidgetPieceNumber::WidgetPieceNumber(ObjectManager* ptrObjManager)
	: Widget(ptrObjManager)
{
}

WidgetPieceNumber::~WidgetPieceNumber()
{
}

bool WidgetPieceNumber::Initialize()
{
	_mPieceNums["PieceStand1"][PIECE::Pawn]	= 0;
	_mPieceNums["PieceStand1"][PIECE::Lance]	= 0;
	_mPieceNums["PieceStand1"][PIECE::Knight]	= 0;
	_mPieceNums["PieceStand1"][PIECE::Silver]	= 0;
	_mPieceNums["PieceStand1"][PIECE::Gold]	= 0;
	_mPieceNums["PieceStand1"][PIECE::Bishop]	= 0;
	_mPieceNums["PieceStand1"][PIECE::Rook]	= 0;

	_mPieceNums["PieceStand2"][PIECE::Pawn]	= 0;
	_mPieceNums["PieceStand2"][PIECE::Lance]	= 0;
	_mPieceNums["PieceStand2"][PIECE::Knight]	= 0;
	_mPieceNums["PieceStand2"][PIECE::Silver]	= 0;
	_mPieceNums["PieceStand2"][PIECE::Gold]	= 0;
	_mPieceNums["PieceStand2"][PIECE::Bishop]	= 0;
	_mPieceNums["PieceStand2"][PIECE::Rook]	= 0;

	return true;
}

bool WidgetPieceNumber::Terminate()
{
	_mPieceNums.clear();
	return true;
}

bool WidgetPieceNumber::Process()
{
	// 各駒台の駒の数を記録する
	for (auto& pieceNum : _mPieceNums) {
		// 駒台の名前を取得
		std::string standName = pieceNum.first;
		auto pieceStand = dynamic_cast<PieceStand*>(_ptrObjManager->Get(standName.c_str()));

		// 駒台にある駒を取得
		std::vector<Piece*> vHasPieces = pieceStand->GetVPieces();

		// vHasPiecesにnullptrがあれば削除する
		vHasPieces.erase(std::remove(vHasPieces.begin(), vHasPieces.end(), nullptr), vHasPieces.end());

		// 駒の種類ごとに数を記録する
		for (auto& type : pieceNum.second) {
			auto pieceType = type.first;
			int nums = std::count_if(vHasPieces.begin(), vHasPieces.end(), [pieceType](Piece* piece) {
				return piece->GetPieceType() == pieceType;
			});
			_mPieceNums[standName][pieceType] = nums;
		}
	}

	return true;
}

bool WidgetPieceNumber::Render()
{
	// 駒台の駒の数を表示する
	for (auto& pieceNum : _mPieceNums) {
		// 駒台の名前を取得
		std::string standName = pieceNum.first;
		auto pieceStand = dynamic_cast<PieceStand*>(_ptrObjManager->Get(standName.c_str()));

		// 駒台にある駒を取得
		std::vector<Piece*> vHasPieces = pieceStand->GetVPieces();

		// vHasPiecesにnullptrがあれば削除する
		vHasPieces.erase(std::remove(vHasPieces.begin(), vHasPieces.end(), nullptr), vHasPieces.end());

		// 駒の種類ごとに数を表示する
		for (auto& type : pieceNum.second) {
			// 一つしか取っていない駒の数は表示しない
			if(type.second < 2) continue;

			// 条件を満たす駒を探す
			auto pieceType = type.first;
			auto ite = std::find_if(vHasPieces.begin(), vHasPieces.end(), [pieceType](Piece* piece) {
				return piece->GetPieceType() == pieceType;
			});

			// 条件を満たす駒がない場合はスキップ
			if (ite == vHasPieces.end()) continue;

			// 駒の位置を取得する
			VECTOR pos = ConvWorldPosToScreenPos((*ite)->GetPos());

			int fontSize = GetFontSize();
			SetFontSize(24);
			DrawFormatString(pos.x + 5, pos.y, GetColor(255, 0, 0), "%d", type.second);
			SetFontSize(fontSize);
		}
	}

	int fontSize = GetFontSize();
	SetFontSize(20);
	DrawString(100, 0, "PieceNumber", GetColor(255, 0, 0));
	SetFontSize(fontSize);

	return true;
}
