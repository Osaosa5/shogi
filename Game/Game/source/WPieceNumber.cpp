
#include "WPieceNumber.h"
#include "PieceStand.h"

WPieceNumber::WPieceNumber(ObjectManager* ptrObjManager)
	: Widget(ptrObjManager)
{
}

WPieceNumber::~WPieceNumber()
{
}

bool WPieceNumber::Initialize()
{
	// 各駒台の駒の数を初期化
	for (const auto& stand : { "PieceStand1", "PieceStand2" }) {
		for (const auto& piece : { PIECE::Pawn, PIECE::Lance, PIECE::Knight, PIECE::Silver, PIECE::Gold, PIECE::Bishop, PIECE::Rook }) {
			_mPieceNums[stand][piece] = 0;
		}
	}

	return true;
}

bool WPieceNumber::Terminate()
{
	_mPieceNums.clear();
	return true;
}

bool WPieceNumber::Process()
{
	std::unordered_map<Piece::PIECE_TYPE, PieceStand::HAS_PIECE_TYPE> pieceTypeMap =
	{
		{Piece::PIECE_TYPE::Pawn,		PieceStand::HAS_PIECE_TYPE::Pawn},
		{Piece::PIECE_TYPE::Lance,		PieceStand::HAS_PIECE_TYPE::Lance},
		{Piece::PIECE_TYPE::Knight,		PieceStand::HAS_PIECE_TYPE::Knight},
		{Piece::PIECE_TYPE::Silver,		PieceStand::HAS_PIECE_TYPE::Silver},
		{Piece::PIECE_TYPE::Gold,		PieceStand::HAS_PIECE_TYPE::Gold},
		{Piece::PIECE_TYPE::Bishop,		PieceStand::HAS_PIECE_TYPE::Bishop},
		{Piece::PIECE_TYPE::Rook,		PieceStand::HAS_PIECE_TYPE::Rook}
	};

	// 各駒台の駒の数を記録する
	for (auto& pieceNum : _mPieceNums) 
	{
		// 駒台の名前を取得
		std::string standName	= pieceNum.first;
		auto		pieceStand	= dynamic_cast<PieceStand*>(_ptrObjManager->Get(standName.c_str()));

		if (!pieceStand) continue;

		auto mPieces = pieceStand->GetMPieces();

		// 駒の数を数える
		for (auto& type : pieceNum.second)
		{
			auto	pieceType	= type.first;
			auto	pieces		= mPieces[pieceTypeMap[pieceType]];
			int		numPieces	= pieces.size();
			_mPieceNums[standName][pieceType] = numPieces;
		}
	}

	return true;
}

bool WPieceNumber::Render()
{
	std::unordered_map<Piece::PIECE_TYPE, PieceStand::HAS_PIECE_TYPE> pieceTypeMap =
	{
		{Piece::PIECE_TYPE::Pawn,		PieceStand::HAS_PIECE_TYPE::Pawn},
		{Piece::PIECE_TYPE::Lance,		PieceStand::HAS_PIECE_TYPE::Lance},
		{Piece::PIECE_TYPE::Knight,		PieceStand::HAS_PIECE_TYPE::Knight},
		{Piece::PIECE_TYPE::Silver,		PieceStand::HAS_PIECE_TYPE::Silver},
		{Piece::PIECE_TYPE::Gold,		PieceStand::HAS_PIECE_TYPE::Gold},
		{Piece::PIECE_TYPE::Bishop,		PieceStand::HAS_PIECE_TYPE::Bishop},
		{Piece::PIECE_TYPE::Rook,		PieceStand::HAS_PIECE_TYPE::Rook}
	};

	// 駒台の駒の数を表示する
	for (auto& pieceNum : _mPieceNums) 
	{
		// 駒台の名前を取得
		std::string standName	= pieceNum.first;
		auto		pieceStand	= dynamic_cast<PieceStand*>(_ptrObjManager->Get(standName.c_str()));

		if (!pieceStand) continue;

		auto mPieces = pieceStand->GetMPieces();

		// 駒の種類ごとに数を表示する
		for (auto& type : pieceNum.second) 
		{
			if (type.second < 2) continue;

			// 駒の位置を取得する
			auto	pieceType	= type.first;
			auto	pieces		= mPieces[pieceTypeMap[pieceType]];

			if (pieces.empty()) continue;

			// 最初の駒の位置を取得する
			VECTOR pos = ConvWorldPosToScreenPos((*pieces.begin())->GetPos());

			int fontSize = GetFontSize();
			SetFontSize(24);
			DrawFormatString(pos.x + 5, pos.y, GetColor(255, 0, 0), "%d", type.second);
			SetFontSize(fontSize);
		}
	}

	return true;
}
