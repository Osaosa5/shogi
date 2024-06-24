
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
	
	// todo:マスを何個選択しているか保持する必要がある

	if (trg & PAD_INPUT_4) {
		// 何も選択していない
		if (!_bSelect) {
			_bSelect = true;
			// 選択したマスを保存
			_saveSquare = std::make_pair(_dan, _suji);
			// 選択したマスを選択済みに変更
			auto square = GetSquare(_dan, _suji);
			square->SetSelect(!square->GetSelect());
		}
		// 選択済み&既に選択したマスと同じマスを選択
		else if (_bSelect && _saveSquare == std::make_pair(_dan, _suji)) {
			_bSelect = false;
			// 保存したマスを未選択に変更
			auto square = GetSquare(_saveSquare.first, _saveSquare.second);
			square->SetSelect(!square->GetSelect());
			// 保存マスを初期化
			_saveSquare = std::make_pair(-1, -1);
		}
		// 選択済み&既に選択したマスと違うマスを選択
		else if (_bSelect && _saveSquare != std::make_pair(_dan, _suji)) {
			_bSelect = false;
			// 駒を選択したマスに動かす
			auto koma = GetKoma(_saveSquare.first, _saveSquare.second);
			koma->SetDan(_dan); koma->SetSuji(_suji);
			koma->SetUpdateBoardPos(true);
			// 保存したマスを未選択に変更
			auto square = GetSquare(_saveSquare.first, _saveSquare.second);
			square->SetSelect(!square->GetSelect());
			// 保存マスを初期化
			_saveSquare = std::make_pair(-1, -1);
		}
	}

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
