
#include "Piece.h"

#include "appframe.h"
#include "Board.h"

Piece::Piece(ObjectManager* objManajer, int dan, int suji, std::string strPlayer)
{
	_objManager = objManajer;
	_oldPos = VGet(0, 0, 0);
	_bUpdate3DPos = true;

	// ��̈ʒu���
	_dan = dan; _suji = suji;
	_tile = _suji * BOARD_SIZE + _dan;

	// �v���C���[���
	if (strPlayer == "player1") _playerType = kPlayer1;
	else if (strPlayer == "player2") _playerType = kPlayer2;
	if (_playerType == kPlayer1) { _rot = VGet(0, 0, 0); }
	else if (_playerType == kPlayer2) { _rot = VGet(0, DEG2RAD(180), 0); }
}

Piece::~Piece()
{
}

bool Piece::Terminate()
{
	return true;
}

bool Piece::Process()
{
	_oldPos = _pos;

	if (_bUpdate3DPos) SetPieceCentralTile();

	return true;
}

bool Piece::Render()
{
	// �p�x�ƈʒu���Z�b�g���ĕ`��
	MV1SetRotationXYZ(_handle, _rot);
	MV1SetPosition(_handle, _pos);
	MV1DrawModel(_handle);

	return true;
}

bool Piece::Move()
{
	return true;
}

void Piece::HitTest()
{
	float colSubY = 40.0f;
	// ��̓����蔻��
	MV1_COLL_RESULT_POLY hitPoly;
	auto shogiBan = _objManager->Get("shogiban");
	auto shogiBanHandle = shogiBan->GetHandle();
	hitPoly = MV1CollCheck_Line(shogiBanHandle, 2,
		VAdd(_pos, VGet(0, colSubY, 0)),
		VAdd(_pos, VGet(0, -999, 0)));
	if (hitPoly.HitFlag)
	{
		// �����ꍇ
		_pos.y = hitPoly.HitPosition.y + 0.3f;
	}
	else
	{
		// ��Ȃ��ꍇ
		_pos = _oldPos;
	}

}

// �^�C���̒����ɋ���Z�b�g���� 
void Piece::SetPieceCentralTile()
{
	// ��Ɠ����ʒu�ɂ���^�C�����擾����
	auto ptrBoard = dynamic_cast<Board*>(_objManager->Get("board"));
	int index = -1;
	for (int y = 0; y < BOARD_SIZE; y++) {
		for (int x = 0; x < BOARD_SIZE; x++) {
			if(ptrBoard->GetPiece(y * BOARD_SIZE + x) == this)	index = y * BOARD_SIZE + x;
		}
	}
	auto ptrSquare = ptrBoard->GetSquare(index);

	// �^�C���̒����ɋ�̈ʒu���Z�b�g����
	this->SetPos(ptrSquare->GetCenter());

	// ��̈ʒu���Z�b�g���ꂽ���Ƃ��L�^����
	_bUpdate3DPos = false;
}
