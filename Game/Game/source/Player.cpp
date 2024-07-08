
#include "Player.h"
#include "Square.h"
#include "Board.h"
#include "ApplicationMain.h"

Player::Player(ObjectManager* objManeger, std::string player)
{
	_objManager = objManeger;
	if (player == "player1") _playerType = PLAYER_TYPE::kPlayer1;
	else if (player == "player2") _playerType = PLAYER_TYPE::kPlayer2;
	else _playerType = PLAYER_TYPE::kNonePlayer;

	_bSelect = false;
	_saveSquare = std::make_pair(-1, -1);

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
	int player = _playerType;
	auto app = ApplicationMain::GetInstance();
	int trg = app->GetTrg(player);

	SelectSquare(trg);
	
	if (trg & PAD_INPUT_4) {


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
	box["lUp"] = pos;
	box["lBottom"] = VGet(pos.x, pos.y, pos.z + size.second);
	box["rUp"] = VGet(pos.x + size.first, pos.y, pos.z);
	box["rBottom"] = VGet(pos.x + size.first, pos.y, pos.z + size.second);
	DrawTriangle3D(box["lUp"], box["lBottom"], box["rBottom"], GetColor(0, 0, 255), TRUE);
	DrawTriangle3D(box["lUp"], box["rUp"], box["rBottom"], GetColor(0, 0, 255), TRUE);
	return true;
}

void Player::SelectSquare(int trg)
{
	if (trg & PAD_INPUT_LEFT) _dan = (_dan + (BOARD_SIZE - 1)) % BOARD_SIZE;
	else if (trg & PAD_INPUT_RIGHT) _dan = (_dan + 1) % BOARD_SIZE;
	if (trg & PAD_INPUT_UP) _suji = (_suji + (BOARD_SIZE - 1)) % BOARD_SIZE;
	else if (trg & PAD_INPUT_DOWN) _suji = (_suji + 1) % BOARD_SIZE;
}

