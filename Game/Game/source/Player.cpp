
#include "Player.h"
#include "Square.h"
#include "Board.h"
#include "ApplicationMain.h"
#include "ModeGame.h"

Player::Player(ObjectManager* objManeger, std::string player, ModeGame* game)
{
	_objManager = objManeger;
	if (player == "player1") _playerType = PLAYER_TYPE::kPlayer1;
	else if (player == "player2") _playerType = PLAYER_TYPE::kPlayer2;
	else _playerType = PLAYER_TYPE::kNonePlayer;
	_game = game;

	_selectedPieceIndex = -1;

	_suji = _dan = 0;
}

Player::~Player()
{
}

bool Player::Terminate()
{
	_vHasPieces.clear();
	return true;
}

bool Player::Process()
{
	int player = _playerType;
	auto app = ApplicationMain::GetInstance();
	int trg = app->GetTrg(player - 1);

	SelectSquare(trg);
	
	int index = _suji * BOARD_SIZE + _dan;
	if (trg & PAD_INPUT_4) {
		if (_selectedPieceIndex == -1) {
			// �����I�����ꂽ�}�X�ɋ����ꍇ�A���I������
			SelectPiece(index);
		}
		else {
			MovePiece(index);
		}	

		return true;
	}
}

bool Player::Render()
{
	auto board = dynamic_cast<Board*>(_objManager->Get("board"));
	auto square = board->GetSquare(_suji * BOARD_SIZE + _dan);
	
	std::unordered_map<std::string, VECTOR> box;
	std::pair<float, float> size = square->GetSize();
	VECTOR pos = square->GetPos();
	int cr = _playerType == PLAYER_TYPE::kPlayer1 ? GetColor(255, 0, 0) : GetColor(0, 0, 255);
	box["lUp"] = pos;
	box["lBottom"] = VGet(pos.x, pos.y, pos.z + size.second);
	box["rUp"] = VGet(pos.x + size.first, pos.y, pos.z);
	box["rBottom"] = VGet(pos.x + size.first, pos.y, pos.z + size.second);
	DrawTriangle3D(box["lUp"], box["lBottom"], box["rBottom"], cr, TRUE);
	DrawTriangle3D(box["lUp"], box["rUp"], box["rBottom"], cr, TRUE);

	int x = _playerType == PLAYER_TYPE::kPlayer1 ? 0 : 32;
	int y = 100;
	int sizeY = 16;
	for (auto& piece : _vHasPieces) {
		PIECE_TYPE type = piece->GetPieceType();
		switch (type) {
			case PIECE_TYPE::kPawn:
				DrawString(x, y, "��", cr); y += sizeY;
				break;
			case PIECE_TYPE::kLance:
				DrawString(x, y, "��", cr); y += sizeY;
				break;
			case PIECE_TYPE::kKnight:
				DrawString(x, y, "�j", cr); y += sizeY;
				break;
			case PIECE_TYPE::kSilver:
				DrawString(x, y, "��", cr); y += sizeY;
				break;
			case PIECE_TYPE::kGold:
				DrawString(x, y, "��", cr); y += sizeY;
				break;
			case PIECE_TYPE::kBishop:
				DrawString(x, y, "�p", cr); y += sizeY;
				break;
			case PIECE_TYPE::kRook:
				DrawString(x, y, "��", cr); y += sizeY;
				break;
			case PIECE_TYPE::kKing:
				DrawString(x, y, "��", cr); y += sizeY;
				break;
			
		}
	}

	return true;
}

void Player::SelectSquare(int trg)
{
	if (trg & PAD_INPUT_LEFT) _dan = (_dan + (BOARD_SIZE - 1)) % BOARD_SIZE;
	else if (trg & PAD_INPUT_RIGHT) _dan = (_dan + 1) % BOARD_SIZE;
	if (trg & PAD_INPUT_UP) _suji = (_suji + (BOARD_SIZE - 1)) % BOARD_SIZE;
	else if (trg & PAD_INPUT_DOWN) _suji = (_suji + 1) % BOARD_SIZE;
}

void Player::SelectPiece(int index)
{
	// ��I������Ă��Ȃ��ꍇ�A�I�������}�X�ɋ���邩�m�F
	auto ptrBoard = dynamic_cast<Board*>(_objManager->Get("board"));
	auto ptrPiece = ptrBoard->GetPiece(index);
	if (ptrPiece == nullptr) return;

	// �����̃R�}�łȂ��ꍇ�A�I���ł��Ȃ�
	if (ptrPiece->GetPlayerType() != _playerType) return;

	// �����ꍇ�A�I�������}�X�̏���ۑ�����
	auto ptrSquare = ptrBoard->GetSquare(index);
	ptrSquare->SetSelect(true);
	_selectedPieceIndex = index;
}

void Player::MovePiece(int index)
{
	// ��I������Ă���ꍇ�A����ړ�
	auto board = dynamic_cast<Board*>(_objManager->Get("board"));
	auto ptrSelectedPiece = board->GetPiece(_selectedPieceIndex);
	auto ptrPiece = board->GetPiece(index);
	// ����̃R�}������ꍇ�A����̃R�}�����
	if (ptrPiece != nullptr && ptrPiece->GetPlayerType() != _playerType) {
		if (ptrPiece->GetPieceType() == PIECE_TYPE::kKing) {
			_game->SetWin(true);
			_game->SetWinPlayer(_playerType == PLAYER_TYPE::kPlayer1 ? "player1" : "player2");
		}
		// ����̃R�}�����
		_vHasPieces.emplace_back(ptrPiece);
		ptrPiece = nullptr;
	}
	// �R�}�̈ʒu����������
	std::swap(ptrPiece, ptrSelectedPiece);

	// ��̔z����X�V
	board->SetPiece(_selectedPieceIndex, ptrSelectedPiece);
	board->SetPiece(index, ptrPiece);

	// �I�����ꂽ�ʒu�ɋ����ꍇ�A��̈ʒu�����X�V
	if (ptrSelectedPiece != nullptr) ptrSelectedPiece->SetUpdate3DPos(true);
	if (ptrPiece != nullptr) ptrPiece->SetUpdate3DPos(true);

	// �I�����ꂽ�ʒu�̋���I����Ԃɂ���
	auto ptrSquare = board->GetSquare(_selectedPieceIndex);
	ptrSquare->SetSelect(false);

	// �I��������̏���������
	_selectedPieceIndex = -1;
}

