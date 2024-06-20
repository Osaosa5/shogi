
#include "Player.h"
#include "Square.h"
#include "ApplicationMain.h"

Player::Player(ObjectManager* objManeger, std::string player)
{
	_objManager = objManeger;
	if (player == "player1") _playerType = PLAYER_TYPE::kPlayer1;
	else if (player == "player2") _playerType = PLAYER_TYPE::kPlayer2;
	else _playerType = PLAYER_TYPE::kNonePlayer;

	_bSelect = false;
	_selectSquare = std::make_pair(-1, -1);

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
	
	// 選択したマスにある駒のポインタを取得
	Koma* koma = GetKoma(_selectSquare.first, _selectSquare.second);

	if (trg & PAD_INPUT_4) {
		if (!_bSelect && GetKoma(_dan, _suji)) {
			_bSelect = true;
			_selectSquare = std::make_pair(_dan, _suji);
			auto square = GetSquare(_dan, _suji);
			square->SetSelect(!square->GetSelect());
		}
		else if (_bSelect && !GetKoma(_dan, _suji)) {
			_bSelect = false;
			auto square = GetSquare(_selectSquare.first, _selectSquare.second);
		}
	}

	auto kaku = _objManager->Get("kaku");
	std::any result = kaku->Get("Dan");

	/*if (trg & PAD_INPUT_4) {
		if (_bSelect && _selectSquare == std::make_pair(_dan, _suji)) {
			_bSelect = false;
			_selectSquare = std::make_pair(-1, -1);
			auto square = GetSquare(_dan, _suji);
			square->SetSelect(!square->GetSelect());
		}
		else if(!_bSelect){
			_bSelect = true;
			_selectSquare = std::make_pair(_dan, _suji);
			auto square = GetSquare(_dan, _suji);
			square->SetSelect(!square->GetSelect());
		}
	}*/

	return true;
}

bool Player::Render()
{
	Square* square = GetSquare(_dan, _suji);

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

Koma* Player::GetKoma(int dan, int suji)
{
	if(dan || suji < 0) return nullptr;
	auto square = GetSquare(dan, suji);
	if (square) return square->GetKoma();
	return nullptr;
}

void Player::SelectSquare(int trg)
{
	if (trg & PAD_INPUT_LEFT) _dan = (_dan + (DAN_MAX - 1)) % DAN_MAX;
	else if (trg & PAD_INPUT_RIGHT) _dan = (_dan + 1) % DAN_MAX;
	if (trg & PAD_INPUT_UP) _suji = (_suji + (SUJI_MAX - 1)) % SUJI_MAX;
	else if (trg & PAD_INPUT_DOWN) _suji = (_suji + 1) % SUJI_MAX;
}

Square* Player::GetSquare(int dan, int suji)
{
	// 駒の位置を文字列に直し、同じ位置にある"square"と合わせる
	std::string strSquare = "square" + std::to_string(suji * DAN_MAX + dan);

	// 駒と同じ位置にあるタイルを取得する
	Object* obj = _objManager->Get(strSquare.c_str());
	if (obj) return dynamic_cast<Square*>(obj);
	else return nullptr;
}

Board* Player::GetBoard()
{
	// 駒と同じ位置にあるタイルを取得する
	Object* obj = _objManager->Get("board");
	if (obj) return dynamic_cast<Board*>(obj);
	else return nullptr;
}
