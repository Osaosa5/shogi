
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
	// �e���̋�̐���������
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

	// �e���̋�̐����L�^����
	for (auto& pieceNum : _mPieceNums) 
	{
		// ���̖��O���擾
		std::string standName	= pieceNum.first;
		auto		pieceStand	= dynamic_cast<PieceStand*>(_ptrObjManager->Get(standName.c_str()));

		if (!pieceStand) continue;

		auto mPieces = pieceStand->GetMPieces();

		// ��̐��𐔂���
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

	// ���̋�̐���\������
	for (auto& pieceNum : _mPieceNums) 
	{
		// ���̖��O���擾
		std::string standName	= pieceNum.first;
		auto		pieceStand	= dynamic_cast<PieceStand*>(_ptrObjManager->Get(standName.c_str()));

		if (!pieceStand) continue;

		auto mPieces = pieceStand->GetMPieces();

		// ��̎�ނ��Ƃɐ���\������
		for (auto& type : pieceNum.second) 
		{
			if (type.second < 2) continue;

			// ��̈ʒu���擾����
			auto	pieceType	= type.first;
			auto	pieces		= mPieces[pieceTypeMap[pieceType]];

			if (pieces.empty()) continue;

			// �ŏ��̋�̈ʒu���擾����
			VECTOR pos = ConvWorldPosToScreenPos((*pieces.begin())->GetPos());

			int fontSize = GetFontSize();
			SetFontSize(24);
			DrawFormatString(pos.x + 5, pos.y, GetColor(255, 0, 0), "%d", type.second);
			SetFontSize(fontSize);
		}
	}

	return true;
}
