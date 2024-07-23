
#include "PieceStand.h"
#include "Square.h"

PieceStand::PieceStand(ObjectManager* objManajer, VECTOR pos, std::string player)
{
	_objManager = objManajer;
	_pos = pos;
	if(player == "player1") _playerType = kPlayer1;
	else if(player == "player2") _playerType = kPlayer2;
	_handle = RM::MV1LoadModel("res/3D/«Šû‚Ì‹î‘ä.mv1");

	// ƒ}ƒX‚Ì’Ç‰Á
	float x = 1.8f;
	float y = 20.1f;
	float z = 1.8f;
	for (int i = 0; i < 7; i++) {
		VECTOR posSquare;
		int dan, suji;
		dan = suji = 0;
		switch (i) {
		case 0:
			posSquare = VGet(_pos.x - SQUARE_WIDTH - x, _pos.y + y, _pos.z + z);
			dan = 0; suji = 0;
			break;
		case 1:
			posSquare = VGet(_pos.x - x, _pos.y + y, _pos.z + z);
			dan = 0; suji = 1;
			break;
		case 2:
			posSquare = VGet(_pos.x + SQUARE_WIDTH - x, _pos.y + y, _pos.z + z);
			dan = 0; suji = 2;
			break;
		case 3:
			posSquare = VGet(_pos.x - SQUARE_WIDTH - x, _pos.y + y, _pos.z - SQUARE_HEIGHT + z);
			dan = 1; suji = 0;
			break;
		case 4:
			posSquare = VGet(_pos.x - x, _pos.y + y, _pos.z - SQUARE_HEIGHT + z);
			dan = 1; suji = 1;
			break;
		case 5:
			posSquare = VGet(_pos.x + SQUARE_WIDTH - x, _pos.y + y, _pos.z - SQUARE_HEIGHT + z);
			dan = 1; suji = 2;
			break;
		case 6:
			posSquare = VGet(_pos.x - SQUARE_WIDTH - x, _pos.y + y, _pos.z - SQUARE_HEIGHT * 2 + z);
			dan = 2; suji = 0;
			break;
		}
		
		_vSquares.emplace_back(new Square(posSquare, player, dan, suji));
		std::string name = "StandSquare" + std::to_string(i);
		_objManager->Add(_vSquares[i], name.c_str());
	}
}

PieceStand::~PieceStand()
{
	_vHasPieces.clear();
}

bool PieceStand::Initialize()
{

	return true;
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
			piece->SetPos(_vSquares[0]->GetCenterPos());
		}
		else if (type == PIECE_TYPE::kLance) {
			piece->SetPos(_vSquares[1]->GetCenterPos());
		}
		else if (type == PIECE_TYPE::kKnight) {
			piece->SetPos(_vSquares[2]->GetCenterPos());
		}
		else if (type == PIECE_TYPE::kSilver) {
			piece->SetPos(_vSquares[3]->GetCenterPos());
		}
		else if (type == PIECE_TYPE::kGold) {
			piece->SetPos(_vSquares[4]->GetCenterPos());
		}
		else if (type == PIECE_TYPE::kBishop) {
			piece->SetPos(_vSquares[5]->GetCenterPos());
		}
		else if (type == PIECE_TYPE::kRook) {
			piece->SetPos(_vSquares[6]->GetCenterPos());
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
