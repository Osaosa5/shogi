
#include "Piece.h"

#include "appframe.h"
#include "Board.h"
#include "PieceStand.h"

Piece::Piece(ObjectManager* objManajer, int dan, int suji, std::string strPlayer)
{
	_objManager		= objManajer;
	_bUpdate3DPos	= true;
	_kOwnerType		= OWNER_TYPE::Board;
	_kPieceState	= PIECE_STATE::None;

	// ��̈ʒu���
	_dan	= dan; 
	_suji	= suji;
	_tile	= _suji * BOARD_SIZE + _dan;

	// �v���C���[���
	if (strPlayer == "player1") _kPlayerType = PLAYER_TYPE::Player1;
	if (strPlayer == "player2") _kPlayerType = PLAYER_TYPE::Player2;
	UpdateDirectionForPlayer(_kPlayerType);

	// ��̈ړ��͈�
	_vMoveRange.resize(MOVE_RANGE_W * MOVE_RANGE_H);
}

Piece::~Piece()
{
}

bool Piece::Terminate()
{
	_vMoveRange.clear();
	return true;
}

bool Piece::Process()
{
	// ��̏�Ԃɂ���ď������ς��
	switch (_kPieceState)
	{
		// ���������Ă��Ȃ��ꍇ
	case PIECE_STATE::None:
		NoneProcess();
		break;
		// ��I������Ă���ꍇ
	case PIECE_STATE::Select:
		SelectProcess();
		break;
		// ��ړ����Ă���ꍇ
	case PIECE_STATE::Move:
		MoveProcess();
		break;
	}

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

bool Piece::NoneProcess()
{
	// ��̃C���f�b�N�X���X�V����
	_tile = _suji * BOARD_SIZE + _dan;

	// ��̈ʒu���X�V����
	if (_bUpdate3DPos)
	{
		// ��̈ʒu���}�X�̒����ɃZ�b�g����
		PutPieceCentralTile();

		// 3D�̈ʒu���X�V�t���O��false�ɂ���
		_bUpdate3DPos = false;
	}

	// ��̌������X�V����
	UpdateDirectionForPlayer(_kPlayerType);

	return true;
}

bool Piece::SelectProcess()
{
	// ��̈ʒu���}�X�̏�����ɂ��炷
	auto ptrBoard = dynamic_cast<Board*>(_objManager->Get("board"));
	auto ptrSquare = ptrBoard->GetSquare(_tile);
	this->_pos.y = ptrSquare->GetCenterPos().y + 1.f;

	// �ړ��ł���}�X�𒲂ׂ�
	if (IsMove(_tile))
	{
		
	}

	return true;
}

bool Piece::MoveProcess()
{
	return true;
}

int Piece::CheckDest(int index, int row, int col)
{
	// �ړ��͈͈͓͂̔��̏ꍇ
	int destRow = index % MOVE_RANGE_W;
	int destCol = index / MOVE_RANGE_H;

	// ��������̋������擾
	int distanceRow = destRow - RANGE_CENTRAL_W;
	int distanceCol = destCol - RANGE_CENTRAL_H;

	// �ړ���̃}�X���擾
	return (col + distanceCol) * BOARD_SIZE + (row + distanceRow);
}

int Piece::CheckCntMovable(int row, int col)
{
	int tileIndex	= 0;
	int moveCnt		= 0;
	for (auto move : _vMoveRange)
	{
		// �ړ��͈͈͂̔͊O�̏ꍇ�̓X�L�b�v
		if (move == 0 || move == 11)
		{
			tileIndex++; continue;
		}

		// �ړ���̃}�X���擾
		int destIndex = CheckDest(tileIndex, row, col);

		// �ړ���̃}�X���͈͊O�̏ꍇ�̓X�L�b�v
		if (destIndex < 0 || destIndex >= BOARD_TILE)
		{
			tileIndex++; continue;
		}

		// �ړ���̃}�X�ɋ���邩�m�F
		auto ptrBoard = dynamic_cast<Board*>(_objManager->Get("board"));
		auto ptrPiece = ptrBoard->GetPiece(destIndex);

		// �ړ���Ɏ����̋����ꍇ�͓������Ȃ�
		if (ptrPiece->GetPlayerType() == _kPlayerType)
		{
			tileIndex++; continue;
		}

		// �ړ���ɑ���̋����ꍇ�͎�邱�Ƃ��ł���
		ptrBoard->GetSquare(destIndex)->SetSquareState("Placeable");
		moveCnt++;
		tileIndex++;
	}

	// �ړ��\�ȃ}�X�̐���Ԃ�
	return moveCnt;
}

bool Piece::IsMove(int index)
{
	// ��̈ʒu�𒲂ׂ�
	int row = index % BOARD_SIZE;
	int col = index / BOARD_SIZE;

	// �ړ��͈͂̊m�F
	int moveCnt		= CheckCntMovable(row, col);

	// �ړ��\�ȃ}�X������ꍇ��true��Ԃ�
	if (moveCnt > 0)	return true;
	else				return false;
}

bool Piece::Move(int index)
{
	// �ړ��\���m�F
	if (!IsMove(index)) return false;

	// �ړ���̃}�X���擾����
	auto ptrBoard = dynamic_cast<Board*>(_objManager->Get("board"));
	auto ptrPiece = ptrBoard->GetPiece(index);

	if (ptrPiece)
	{
		int tmp = ptrPiece->GetDan();
		ptrPiece->SetDan(_dan);
		_dan = tmp;

		tmp = ptrPiece->GetSuji();
		ptrPiece->SetSuji(_suji);
		_suji = tmp;
	}
	else
	{
		ptrBoard->SetPiece(index, ptrPiece);
		ptrBoard->SetPiece(_tile, nullptr);
	}

	// ��̈ʒu�����X�V
	


	return true;
}

// �^�C���̒����ɋ���Z�b�g���� 
void Piece::PutPieceCentralTile()
{
	// �����ꏊ���擾����
	auto owner = this->GetOwnerType();

	VECTOR pos = { 0, 0, 0 };

	// ��Ɠ����ʒu�ɂ���^�C�����擾����
	if (owner == OWNER_TYPE::Board)
	{
		auto ptrBoard = dynamic_cast<Board*>(_objManager->Get("board"));
		auto ptrSquare = ptrBoard->GetSquare(this->_suji * BOARD_SIZE + this->_dan);
		pos = ptrSquare->GetCenterPos();
	}
	else if(owner == OWNER_TYPE::PieceStand)
	{
		std::string strPieceStand = "PieceStand";
		strPieceStand += _kPlayerType == PLAYER_TYPE::Player1 ? "1" : "2";
		auto ptrPieceStand = dynamic_cast<PieceStand*>(_objManager->Get(strPieceStand.c_str()));

		auto ptrSquare = ptrPieceStand->GetSquare(this->_suji * PIECESTAND_W + this->_dan);
		pos = ptrSquare->GetCenterPos();
	}

	// ��̈ʒu��������ɂ��炷
	// �}�X�̍��W�����̂܂܂��Z�b�g����ƁA������������܂��Ă��܂�����
	pos.y += 0.5f;

	// �^�C���̒����ɋ�̈ʒu���Z�b�g����
	this->SetPos(pos);
}

void Piece::UpdateDirectionForPlayer(PLAYER_TYPE playerType)
{
	if (_kOwnerType == OWNER_TYPE::Board) 
	{
		if (playerType == PLAYER_TYPE::Player1) { _rot = VGet(0, 0, 0); }
		if (playerType == PLAYER_TYPE::Player2) { _rot = VGet(0, DEG2RAD(180), 0); }
	}
	else if (_kOwnerType == OWNER_TYPE::PieceStand)
	{
		_rot = VGet(0, 0, 0);
	}
}

