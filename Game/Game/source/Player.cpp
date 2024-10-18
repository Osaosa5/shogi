
#include "Player.h"
#include "Square.h"
#include "Board.h"
#include "PieceStand.h"
#include "ApplicationMain.h"
#include "ModeGame.h"

Player::Player(ObjectManager* objManeger, std::string player, ModeGame* game)
{
	_objManager = objManeger;
	_game		= game;

	if (player == "player1") _kPlayerType = PLAYER_TYPE::Player1;
	if (player == "player2") _kPlayerType = PLAYER_TYPE::Player2;
}

Player::~Player()
{
}

bool Player::Initialize()
{
	_suji = _dan = 0;
	_selectedPieceIndex = -1;

	_selectSquareBoard = std::make_pair(_dan, _suji);
	_selectSquareStand = std::make_pair(_dan, _suji);

	_state = PLAYER_STATE::BoardSquare;

	_isSelectPieceOfPieceStand = false;

	return true;
}

bool Player::Terminate()
{
	return true;
}

bool Player::Process()
{
	int		player	= ConvertEnumToInt<PLAYER_TYPE>(_kPlayerType);
	auto	app		= ApplicationMain::GetInstance();
	int		trg		= 0;

#ifdef _DEBUG
	trg = app->GetTrg(player - 1);
#else
	trg = app->GetTrg(player);
#endif 

	// �����ՑI�������I������؂�ւ���
	if (trg & PAD_INPUT_2)
	{
		if (_state == PLAYER_STATE::BoardSquare)
		{
			ChangeSelectBoardToStand();
		}
		else if (_state == PLAYER_STATE::PieceStandSquare)
		{
			ChangeSelectStandToBoard();
		}
	}

	// �}�X��I��
	SelectSquare(trg);
	
	// �^�[���������̃^�[���łȂ��ꍇ�A�������s��Ȃ�
	std::string strMyName			= _objManager->GetName(this);
	std::string strCurrentPlayer	= _game->GetCurrentPlayer();
	if(strCurrentPlayer != strMyName) return false;

	int index = _suji * BOARD_SIZE + _dan;
	if (trg & PAD_INPUT_4) 
	{
		// �����Ղ̃}�X��I������
		if(_state == PLAYER_STATE::BoardSquare && _selectedPieceIndex == -1) SelectBoardPiece(index);
		
		else if(_state == PLAYER_STATE::DestBoardSquare) MoveBoardPiece(index);

		// ���̃}�X��I������
		else if(_state == PLAYER_STATE::PieceStandSquare && _selectedPieceIndex == -1)
		{
			index = _suji* PIECESTAND_W + _dan;
			SelectStandPiece(index);
		}

		else if(_state == PLAYER_STATE::DestPieceStandSquare && _selectedPieceIndex != -1) MoveStandPiece(index);
	}

	return true;
}

bool Player::Render()
{
	std::unordered_map<std::string, VECTOR> box;
	std::pair<float, float>					size;
	VECTOR									pos = { 0,0,0 };

	if (_state == PLAYER_STATE::BoardSquare 
	 || _state == PLAYER_STATE::DestBoardSquare
	 || _state == PLAYER_STATE::DestPieceStandSquare)
	{
		auto board	 = dynamic_cast<Board*>(_objManager->Get("board"));
		auto square	 = board->GetSquare(_suji * BOARD_SIZE + _dan);

		size	= square->GetSize();
		pos		= square->GetPos();
	}
	else if (_state == PLAYER_STATE::PieceStandSquare)
	{
		std::string strPieceStand	= "PieceStand";
		strPieceStand				+= _kPlayerType == PLAYER_TYPE::Player1 ? "1" : "2";
		auto pieceStand				= dynamic_cast<PieceStand*>(_objManager->Get(strPieceStand.c_str()));

		auto square = pieceStand->GetSquare(_suji * PIECESTAND_W + _dan);

		size	= square->GetSize();
		pos		= square->GetPos();
	}
	
	int cr		= _kPlayerType == PLAYER_TYPE::Player1 ? GetColor(255, 0, 0) : GetColor(0, 0, 255);

	box["lUp"]		= pos;
	box["lBottom"]	= VGet(pos.x, pos.y, pos.z + size.second);
	box["rUp"]		= VGet(pos.x + size.first, pos.y, pos.z);
	box["rBottom"]	= VGet(pos.x + size.first, pos.y, pos.z + size.second);

	DrawTriangle3D(box["lUp"], box["lBottom"],	box["rBottom"], cr, TRUE);
	DrawTriangle3D(box["lUp"], box["rUp"],		box["rBottom"], cr, TRUE);
	
	return true;
}

void Player::SelectSquare(int trg)
{
	if (_state == PLAYER_STATE::PieceStandSquare)
	{

		if (_suji == 2)	_dan = SelectFocus(trg, "x", PIECESTAND_W - 2, _dan);
		else			_dan = SelectFocus(trg, "x", PIECESTAND_W, _dan);

		if (_dan > 0)	_suji = SelectFocus(trg, "y", PIECESTAND_H - 1, _suji);
		else			_suji = SelectFocus(trg, "y", PIECESTAND_H, _suji);
	} 
	else if (_state == PLAYER_STATE::DestPieceStandSquare
		  || _state == PLAYER_STATE::BoardSquare
		  || _state == PLAYER_STATE::DestBoardSquare)
	{
		_dan	= SelectFocus(trg, "x", BOARD_SIZE, _dan);
		_suji	= SelectFocus(trg, "y", BOARD_SIZE, _suji);
	}
}

void Player::SelectBoardSquare(int index)
{
	if (_selectedPieceIndex == -1)
	{
		// �����I�����ꂽ�}�X�ɋ����ꍇ�A���I������
		SelectBoardPiece(index);
	}
	else
	{
		MoveBoardPiece(index);
	}
}

void Player::SelectPieceStandSquare(int index)
{
	if (_selectedPieceIndex == -1)
	{
		// �����I�����ꂽ�}�X�ɋ����ꍇ�A���I������
		SelectStandPiece(index);
	}
	else
	{
		MoveStandPiece(index);
	}
}

void Player::ChangeSelectBoardToStand()
{
	// ���I���ɐ؂�ւ���
	_state = PLAYER_STATE::PieceStandSquare;

	// �I�����ꂽ�}�X�̏���ۑ�����
	_selectSquareBoard = std::make_pair(_dan, _suji);

	// ���I�����̑I�����Ă����}�X������
	_dan	= _selectSquareStand.first;
	_suji	= _selectSquareStand.second;
}

void Player::ChangeSelectDestinationBoard()
{
	// �����Ղɂ����̈ړ���I���ɐ؂�ւ���
	_state = PLAYER_STATE::DestBoardSquare;
}

void Player::ChangeSelectStandToBoard()
{
	// �����ՑI���ɐ؂�ւ���
	_state = PLAYER_STATE::BoardSquare;

	// �I�����ꂽ�}�X�̏���ۑ�����
	_selectSquareStand = std::make_pair(_dan, _suji);

	// �����ՑI�����̑I�����Ă����}�X������
	_dan	= _selectSquareBoard.first;
	_suji	= _selectSquareBoard.second;
}

void Player::ChangeSelectDestinationStandToBoard()
{
	// ���ɂ����̈ړ���I���ɐ؂�ւ���
	_state = PLAYER_STATE::DestPieceStandSquare;

	// �I�����ꂽ�}�X�̏���ۑ�����
	_selectSquareStand = std::make_pair(_dan, _suji);

	// �����ՑI�����̑I�����Ă����}�X������
	_dan	= _selectSquareBoard.first;
	_suji	= _selectSquareBoard.second;
}

void Player::SelectBoardPiece(int index)
{
	// ��I������Ă��Ȃ��ꍇ�A�I�������}�X�ɋ���邩�m�F
	auto ptrBoard = dynamic_cast<Board*>(_objManager->Get("board"));
	auto ptrPiece = ptrBoard->GetPiece(index);

	// ��Ȃ��ꍇ�A�����𒆒f
	if (ptrPiece == nullptr) return;

	// �����̃R�}�łȂ��ꍇ�A�I���ł��Ȃ�
	if (ptrPiece->GetPlayerType() != _kPlayerType) return;

	// �����ꍇ�A�I�������}�X�̏���ۑ�����
	auto ptrSquare		= ptrBoard->GetSquare(index);
	ptrSquare			->SetSelect(true);
	_selectedPieceIndex = index;

	ChangeSelectDestinationBoard();
}

void Player::MoveBoardPiece(int index)
{
	// ��I������Ă���ꍇ�A����ړ�
	auto board				= dynamic_cast<Board*>(_objManager->Get("board"));
	auto ptrSelectedPiece	= board->GetPiece(_selectedPieceIndex);
	auto ptrPiece			= board->GetPiece(index);

	// ����̋����ꍇ�A������
	ptrPiece = TakePiece(ptrPiece);

	// �R�}�̈ʒu����������
	std::swap(ptrPiece, ptrSelectedPiece);

	// �R�}�̈ʒu�����X�V
	ptrPiece->SetDan(_dan);
	ptrPiece->SetSuji(_suji);

	// ��̔z����X�V
	board->SetPiece(_selectedPieceIndex, ptrSelectedPiece);
	board->SetPiece(index, ptrPiece);

	// �I�����ꂽ�ʒu�ɋ����ꍇ�A��̈ʒu�����X�V
	if (ptrSelectedPiece	!= nullptr)	ptrSelectedPiece->SetUpdate3DPos(true);
	if (ptrPiece			!= nullptr)	ptrPiece		->SetUpdate3DPos(true);

	// �I�����ꂽ�ʒu�̋���I����Ԃɂ���
	auto ptrSquare	= board->GetSquare(_selectedPieceIndex);
	ptrSquare		->SetSelect(false);

	// �I��������̏���������
	_selectedPieceIndex = -1;

	_state = PLAYER_STATE::BoardSquare;

	// �v���C���[����シ��
	_game->ChangeCurrentPlayer();
}

Piece* Player::TakePiece(Piece* ptrPiece)
{
	// �w�肳�ꂽ�C���f�b�N�X�̋���݂��Ȃ��ꍇ�͏����𒆒f
	if(!ptrPiece) return ptrPiece;

	// �����̋���w�肳�ꂽ�ꍇ�A�����𒆒f
	if(ptrPiece->GetPlayerType() == _kPlayerType) return ptrPiece;

	 // ����̃L���O��������ꍇ�A�����������s��
	if (ptrPiece->GetPieceType() == PIECE_TYPE::King) 
	{
		_game->SetWin(true);
		_game->SetWinPlayer(_kPlayerType == PLAYER_TYPE::Player1 ? "player1" : "player2");
		return nullptr;
	}

	// ����̋�������̎�����ɒǉ�
	ptrPiece->SetPlayerType(_kPlayerType);
	ptrPiece->SetOwnerType(Piece::OWNER_TYPE::PieceStand);

	// ����̋�������̋��ɒu��
	std::string strPieceStand	= "PieceStand";
	strPieceStand				+= _kPlayerType == PLAYER_TYPE::Player1 ? "1" : "2";
	auto pieceStand				= dynamic_cast<PieceStand*>(_objManager->Get(strPieceStand.c_str()));

	pieceStand->AddPiece(ptrPiece);

	return nullptr;
}

void Player::SelectStandPiece(int index)
{
	// ���̖��O
	std::string strPieceStand	= "PieceStand";
	strPieceStand				+= _kPlayerType == PLAYER_TYPE::Player1 ? "1" : "2";

	// ��I������Ă��Ȃ��ꍇ�A�I�������}�X�ɋ���邩�m�F
	auto						ptrStand	= dynamic_cast<PieceStand*>(_objManager->Get(strPieceStand.c_str()));
	PieceStand::HAS_PIECE_TYPE	type		= ConvertIntToEnum<PieceStand::HAS_PIECE_TYPE>(index);
	auto						ptrPiece	= ptrStand->GetMPiece(type);

	// ��Ȃ��ꍇ�A�����𒆒f
	if (ptrPiece == nullptr) return;

	// �����ꍇ�A�I�������}�X�̏���ۑ�����
	auto ptrSquare	= ptrStand->GetSquare(index);
	ptrSquare		->SetSelect(true);

	_selectedPieceIndex			= index;
	_isSelectPieceOfPieceStand	= true;

	ChangeSelectDestinationStandToBoard();
}

void Player::MoveStandPiece(int index)
{
	// ��I������Ă���ꍇ�A����ړ�
	std::string strPieceStand	= "PieceStand";
	strPieceStand				+= _kPlayerType == PLAYER_TYPE::Player1 ? "1" : "2";

	auto pieceStand			= dynamic_cast<PieceStand*>(_objManager->Get(strPieceStand.c_str()));
	auto ptrBoard			= dynamic_cast<Board*>(_objManager->Get("board"));

	auto ptrSelectedPiece	= pieceStand->GetMPiece(ConvertIntToEnum<PieceStand::HAS_PIECE_TYPE>(_selectedPieceIndex));
	auto ptrPiece			= ptrBoard	->GetPiece(index);

	// �����ꍇ�A�����𒆒f
	if(ptrPiece) return;

	// �R�}�̈ʒu����������
	ptrSelectedPiece->SetDan(_dan);
	ptrSelectedPiece->SetSuji(_suji);
	ptrSelectedPiece->SetOwnerType(Piece::OWNER_TYPE::Board);
	std::swap(ptrPiece, ptrSelectedPiece);

	// ��̔z����X�V
	pieceStand	->RemovePiece(ptrPiece);
	ptrBoard	->SetPiece(index, ptrPiece);

	// �I�����ꂽ�ʒu�ɋ����ꍇ�A��̈ʒu�����X�V
	if (ptrPiece != nullptr) ptrPiece->SetUpdate3DPos(true);

	// �I�����ꂽ�ʒu�̋���I����Ԃɂ���
	auto ptrSquare	= pieceStand->GetSquare(_selectedPieceIndex);
	ptrSquare		->SetSelect(false);

	// �I��������̏���������
	_selectedPieceIndex			= -1;
	_isSelectPieceOfPieceStand	= false;

	_state = PLAYER_STATE::BoardSquare;

	// �v���C���[����シ��
	_game->ChangeCurrentPlayer();
}



