
#include "PieceStand.h"

PieceStand::PieceStand(ObjectManager* objManajer, VECTOR pos, std::string player)
{
	_objManager = objManajer;
	_pos = pos;
	if(player == "player1") _playerType = kPlayer1;
	else if(player == "player2") _playerType = kPlayer2;
	_handle = RM::MV1LoadModel("res/3D/�����̋��.mv1");
}

PieceStand::~PieceStand()
{
	_vHasPieces.clear();
}

bool PieceStand::Terminate()
{
	return true;
}

bool PieceStand::Process()
{
	if(_vHasPieces.empty()) return false;

	float x = 3.f;
	float y = 21.5f;
	float z = 3.f;
	for (auto& piece : _vHasPieces) {
		auto type = piece->GetPieceType();
		if (type == PIECE_TYPE::kPawn) {
			piece->SetPos(VGet(_pos.x - x, _pos.y + y, _pos.z + z));
		}
		else if (type == PIECE_TYPE::kLance) {
			piece->SetPos(VGet(_pos.x, _pos.y + y, _pos.z + z));
		}
		else if (type == PIECE_TYPE::kKnight) {
			piece->SetPos(VGet(_pos.x + x, _pos.y + y, _pos.z + z));
		}
		else if (type == PIECE_TYPE::kSilver) {
			piece->SetPos(VGet(_pos.x - x, _pos.y + y, _pos.z));
		}
		else if (type == PIECE_TYPE::kGold) {
			piece->SetPos(VGet(_pos.x, _pos.y + y, _pos.z));
		}
		else if (type == PIECE_TYPE::kBishop) {
			piece->SetPos(VGet(_pos.x + x, _pos.y + y, _pos.z));
		}
		else if (type == PIECE_TYPE::kRook) {
			piece->SetPos(VGet(_pos.x - x, _pos.y + y, _pos.z - z));
		}
	}

	return true;
}

bool PieceStand::Render()
{
	MV1SetPosition(_handle, _pos);
	MV1DrawModel(_handle);
	return true;
}
