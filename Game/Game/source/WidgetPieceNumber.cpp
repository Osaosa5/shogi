
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
	_mPieceNums["PieceStand1"][PIECE::kPawn]	= 0;
	_mPieceNums["PieceStand1"][PIECE::kLance]	= 0;
	_mPieceNums["PieceStand1"][PIECE::kKnight]	= 0;
	_mPieceNums["PieceStand1"][PIECE::kSilver]	= 0;
	_mPieceNums["PieceStand1"][PIECE::kGold]	= 0;
	_mPieceNums["PieceStand1"][PIECE::kBishop]	= 0;
	_mPieceNums["PieceStand1"][PIECE::kRook]	= 0;

	_mPieceNums["PieceStand2"][PIECE::kPawn]	= 0;
	_mPieceNums["PieceStand2"][PIECE::kLance]	= 0;
	_mPieceNums["PieceStand2"][PIECE::kKnight]	= 0;
	_mPieceNums["PieceStand2"][PIECE::kSilver]	= 0;
	_mPieceNums["PieceStand2"][PIECE::kGold]	= 0;
	_mPieceNums["PieceStand2"][PIECE::kBishop]	= 0;
	_mPieceNums["PieceStand2"][PIECE::kRook]	= 0;

	return true;
}

bool WidgetPieceNumber::Terminate()
{
	_mPieceNums.clear();
	return true;
}

bool WidgetPieceNumber::Process()
{
	// �e���̋�̐����L�^����
	for (auto& pieceNum : _mPieceNums) {
		// ���̖��O���擾
		std::string standName = pieceNum.first;
		auto pieceStand = dynamic_cast<PieceStand*>(_ptrObjManager->Get(standName.c_str()));

		// ���ɂ������擾
		std::vector<Piece*> vHasPieces = pieceStand->GetVPieces();

		// vHasPieces��nullptr������΍폜����
		vHasPieces.erase(std::remove(vHasPieces.begin(), vHasPieces.end(), nullptr), vHasPieces.end());

		// ��̎�ނ��Ƃɐ����L�^����
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
	// ���̋�̐���\������
	for (auto& pieceNum : _mPieceNums) {
		// ���̖��O���擾
		std::string standName = pieceNum.first;
		auto pieceStand = dynamic_cast<PieceStand*>(_ptrObjManager->Get(standName.c_str()));

		// ���ɂ������擾
		std::vector<Piece*> vHasPieces = pieceStand->GetVPieces();

		// vHasPieces��nullptr������΍폜����
		vHasPieces.erase(std::remove(vHasPieces.begin(), vHasPieces.end(), nullptr), vHasPieces.end());

		// ��̎�ނ��Ƃɐ���\������
		for (auto& type : pieceNum.second) {
			// ���������Ă��Ȃ���̐��͕\�����Ȃ�
			if(type.second < 2) continue;

			// �����𖞂������T��
			auto pieceType = type.first;
			auto ite = std::find_if(vHasPieces.begin(), vHasPieces.end(), [pieceType](Piece* piece) {
				return piece->GetPieceType() == pieceType;
			});

			// �����𖞂�����Ȃ��ꍇ�̓X�L�b�v
			if (ite == vHasPieces.end()) continue;

			// ��̈ʒu���擾����
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