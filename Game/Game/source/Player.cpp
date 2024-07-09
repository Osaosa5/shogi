
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
			// もし選択されたマスに駒がある場合、駒を選択する
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
				DrawString(x, y, "歩", cr); y += sizeY;
				break;
			case PIECE_TYPE::kLance:
				DrawString(x, y, "香", cr); y += sizeY;
				break;
			case PIECE_TYPE::kKnight:
				DrawString(x, y, "桂", cr); y += sizeY;
				break;
			case PIECE_TYPE::kSilver:
				DrawString(x, y, "銀", cr); y += sizeY;
				break;
			case PIECE_TYPE::kGold:
				DrawString(x, y, "金", cr); y += sizeY;
				break;
			case PIECE_TYPE::kBishop:
				DrawString(x, y, "角", cr); y += sizeY;
				break;
			case PIECE_TYPE::kRook:
				DrawString(x, y, "飛", cr); y += sizeY;
				break;
			case PIECE_TYPE::kKing:
				DrawString(x, y, "玉", cr); y += sizeY;
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
	// 駒が選択されていない場合、選択したマスに駒があるか確認
	auto ptrBoard = dynamic_cast<Board*>(_objManager->Get("board"));
	auto ptrPiece = ptrBoard->GetPiece(index);
	if (ptrPiece == nullptr) return;

	// 自分のコマでない場合、選択できない
	if (ptrPiece->GetPlayerType() != _playerType) return;

	// 駒がある場合、選択したマスの情報を保存する
	auto ptrSquare = ptrBoard->GetSquare(index);
	ptrSquare->SetSelect(true);
	_selectedPieceIndex = index;
}

void Player::MovePiece(int index)
{
	// 駒が選択されている場合、駒を移動
	auto board = dynamic_cast<Board*>(_objManager->Get("board"));
	auto ptrSelectedPiece = board->GetPiece(_selectedPieceIndex);
	auto ptrPiece = board->GetPiece(index);
	// 相手のコマがある場合、相手のコマを取る
	if (ptrPiece != nullptr && ptrPiece->GetPlayerType() != _playerType) {
		if (ptrPiece->GetPieceType() == PIECE_TYPE::kKing) {
			_game->SetWin(true);
			_game->SetWinPlayer(_playerType == PLAYER_TYPE::kPlayer1 ? "player1" : "player2");
		}
		// 相手のコマを取る
		_vHasPieces.emplace_back(ptrPiece);
		ptrPiece = nullptr;
	}
	// コマの位置を交換する
	std::swap(ptrPiece, ptrSelectedPiece);

	// 駒の配列を更新
	board->SetPiece(_selectedPieceIndex, ptrSelectedPiece);
	board->SetPiece(index, ptrPiece);

	// 選択された位置に駒がある場合、駒の位置情報を更新
	if (ptrSelectedPiece != nullptr) ptrSelectedPiece->SetUpdate3DPos(true);
	if (ptrPiece != nullptr) ptrPiece->SetUpdate3DPos(true);

	// 選択された位置の駒を非選択状態にする
	auto ptrSquare = board->GetSquare(_selectedPieceIndex);
	ptrSquare->SetSelect(false);

	// 選択した駒の情報を初期化
	_selectedPieceIndex = -1;
}

