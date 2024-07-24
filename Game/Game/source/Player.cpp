
#include "Player.h"
#include "Square.h"
#include "Board.h"
#include "PieceStand.h"
#include "ApplicationMain.h"
#include "ModeGame.h"

#define ON_DEBUG

Player::Player(ObjectManager* objManeger, std::string player, ModeGame* game)
{
	_objManager = objManeger;
	_game = game;

	if (player == "player1") _playerType = PLAYER_TYPE::kPlayer1;
	if (player == "player2") _playerType = PLAYER_TYPE::kPlayer2;
	
	_selectedPieceIndex = -1;
	_suji = _dan = 0;
}

Player::~Player()
{
}

bool Player::Terminate()
{
	return true;
}

bool Player::Process()
{
	int		player	= _playerType;
	auto	app		= ApplicationMain::GetInstance();
	int		trg		= app->GetTrg(player - 1);

#ifdef ON_DEBUG
	trg = app->GetTrg(player - 1);
#else
	trg = app->GetTrg(player);
#endif 

	// �}�X��I��
	SelectSquare(trg);
	
	// �^�[���������̃^�[���łȂ��ꍇ�A�������s��Ȃ�
	std::string strMyName			= _objManager->GetName(this);
	std::string strCurrentPlayer	= _game->GetCurrentPlayer();
	if(strCurrentPlayer != strMyName) return false;

	int index = _suji * BOARD_SIZE + _dan;
	if (trg & PAD_INPUT_4) 
	{
		if (_selectedPieceIndex == -1) 
		{
			// �����I�����ꂽ�}�X�ɋ����ꍇ�A���I������
			SelectPiece(index);
		}
		else 
		{
			MovePiece(index);
			_game->ChangeCurrentPlayer();
		}	
	}

	return true;
}

bool Player::Render()
{
	auto board	= dynamic_cast<Board*>(_objManager->Get("board"));
	auto square = board->GetSquare(_suji * BOARD_SIZE + _dan);
	
	std::unordered_map<std::string, VECTOR> box;
	std::pair<float, float>					size	= square->GetSize();
	VECTOR									pos		= square->GetPos();

	int cr		= _playerType == PLAYER_TYPE::kPlayer1 ? GetColor(255, 0, 0) : GetColor(0, 0, 255);

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
	_dan	= SelectFocus(trg, "x", BOARD_SIZE, _dan);
	_suji	= SelectFocus(trg, "y", BOARD_SIZE, _suji);
}

void Player::SelectPiece(int index)
{
	// ��I������Ă��Ȃ��ꍇ�A�I�������}�X�ɋ���邩�m�F
	auto ptrBoard = dynamic_cast<Board*>(_objManager->Get("board"));
	auto ptrPiece = ptrBoard->GetPiece(index);

	// ��Ȃ��ꍇ�A�����𒆒f
	if (ptrPiece == nullptr) return;

	// �����̃R�}�łȂ��ꍇ�A�I���ł��Ȃ�
	if (ptrPiece->GetPlayerType() != _playerType) return;

	// �����ꍇ�A�I�������}�X�̏���ۑ�����
	auto ptrSquare		= ptrBoard->GetSquare(index);
	ptrSquare			->SetSelect(true);
	_selectedPieceIndex = index;
}

void Player::MovePiece(int index)
{
	// ��I������Ă���ꍇ�A����ړ�
	auto board				= dynamic_cast<Board*>(_objManager->Get("board"));
	auto ptrSelectedPiece	= board->GetPiece(_selectedPieceIndex);
	auto ptrPiece			= board->GetPiece(index);

	TakePiece(ptrPiece);

	// �R�}�̈ʒu����������
	std::swap(ptrPiece, ptrSelectedPiece);

	// ��̔z����X�V
	board->SetPiece(_selectedPieceIndex, ptrSelectedPiece);
	board->SetPiece(index, ptrPiece);

	// �I�����ꂽ�ʒu�ɋ����ꍇ�A��̈ʒu�����X�V
	if (ptrSelectedPiece != nullptr)	ptrSelectedPiece->SetUpdate3DPos(true);
	if (ptrPiece != nullptr)			ptrPiece->SetUpdate3DPos(true);

	// �I�����ꂽ�ʒu�̋���I����Ԃɂ���
	auto ptrSquare	= board->GetSquare(_selectedPieceIndex);
	ptrSquare		->SetSelect(false);

	// �I��������̏���������
	_selectedPieceIndex = -1;
}

void Player::TakePiece(Piece* ptrPiece)
{
	// �w�肳�ꂽ�C���f�b�N�X�̋���݂��Ȃ��ꍇ�͏����𒆒f
	if(!ptrPiece) return;

	// �����̋���w�肳�ꂽ�ꍇ�A�����𒆒f
	if(ptrPiece->GetPlayerType() == _playerType) return;

	 // ����̃L���O��������ꍇ�A�����������s��
	if (ptrPiece->GetPieceType() == PIECE_TYPE::kKing) 
	{
		_game->SetWin(true);
		_game->SetWinPlayer(_playerType == PLAYER_TYPE::kPlayer1 ? "player1" : "player2");
		return;
	}

	// ����̋�������̎�����ɒǉ�
	ptrPiece->SetPlayerType(_playerType);
	ptrPiece->SetOwnerType(Piece::OWNER_TYPE::kPieceStand);

	// ����̋�������̋��ɒu��
	std::string strPieceStand	= "PieceStand";
	strPieceStand				+= _playerType == PLAYER_TYPE::kPlayer1 ? "1" : "2";
	auto pieceStand				= dynamic_cast<PieceStand*>(_objManager->Get(strPieceStand.c_str()));

	pieceStand->AddPiece(ptrPiece);
}

