
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
	
	// todo:�}�X�����I�����Ă��邩�ێ�����K�v������

	if (trg & PAD_INPUT_4) {
		// �����I�����Ă��Ȃ�
		if (!_bSelect) {
			_bSelect = true;
			// �I�������}�X��ۑ�
			_saveSquare = std::make_pair(_dan, _suji);
			// �I�������}�X��I���ς݂ɕύX
			auto square = GetSquare(_dan, _suji);
			square->SetSelect(!square->GetSelect());
		}
		// �I���ς�&���ɑI�������}�X�Ɠ����}�X��I��
		else if (_bSelect && _saveSquare == std::make_pair(_dan, _suji)) {
			_bSelect = false;
			// �ۑ������}�X�𖢑I���ɕύX
			auto square = GetSquare(_saveSquare.first, _saveSquare.second);
			square->SetSelect(!square->GetSelect());
			// �ۑ��}�X��������
			_saveSquare = std::make_pair(-1, -1);
		}
		// �I���ς�&���ɑI�������}�X�ƈႤ�}�X��I��
		else if (_bSelect && _saveSquare != std::make_pair(_dan, _suji)) {
			_bSelect = false;
			// ���I�������}�X�ɓ�����
			auto koma = GetKoma(_saveSquare.first, _saveSquare.second);
			koma->SetDan(_dan); koma->SetSuji(_suji);
			koma->SetUpdateBoardPos(true);
			// �ۑ������}�X�𖢑I���ɕύX
			auto square = GetSquare(_saveSquare.first, _saveSquare.second);
			square->SetSelect(!square->GetSelect());
			// �ۑ��}�X��������
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
	// ��̈ʒu�𕶎���ɒ����A�����ʒu�ɂ���"square"�ƍ��킹��
	std::string strSquare = "square" + std::to_string(suji * DAN_MAX + dan);

	// ��Ɠ����ʒu�ɂ���^�C�����擾����
	Object* obj = _objManager->Get(strSquare.c_str());
	if (obj) return dynamic_cast<Square*>(obj);
	else return nullptr;
}
