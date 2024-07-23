
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

#ifdef ON_DEBUG
	trg = app->GetTrg(player - 1);
#else
	trg = app->GetTrg(player);
#endif 


	SelectSquare(trg);
	
	// ターンが自分のターンでない場合、処理を行わない
	std::string strMyName = _objManager->GetName(this);
	std::string strCurrentPlayer = _game->GetCurrentPlayer();
	if(strCurrentPlayer != strMyName) return false;

	int index = _suji * BOARD_SIZE + _dan;
	if (trg & PAD_INPUT_4) {
		if (_selectedPieceIndex == -1) {
			// もし選択されたマスに駒がある場合、駒を選択する
			SelectPiece(index);
		}
		else {
			MovePiece(index);
			_game->SetCurrentPlayer(strCurrentPlayer == "player1" ? "player2" : "player1");
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
	
	return true;
}

void Player::SelectSquare(int trg)
{
	_dan	= SelectFocus(trg, "x", BOARD_SIZE, _dan);
	_suji	= SelectFocus(trg, "y", BOARD_SIZE, _suji);
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
		ptrPiece->SetPlayerType(_playerType);
		std::string strPieceStand = "PieceStand";
		std::string strNum = _playerType == PLAYER_TYPE::kPlayer1 ? "1" : "2";
		strPieceStand += strNum;
		auto pieceStand = dynamic_cast<PieceStand*>(_objManager->Get(strPieceStand.c_str()));
		pieceStand->AddPiece(ptrPiece);
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

