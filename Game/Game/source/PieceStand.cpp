
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
	_mHasPieces.clear();
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

	// _vHasPieces‚Énullptr‚ª‚ ‚ê‚Îíœ‚·‚é
	_vHasPieces.erase(std::remove(_vHasPieces.begin(), _vHasPieces.end(), nullptr), _vHasPieces.end());

	// _mHasPieces‚Énullptr‚ª‚ ‚ê‚Îíœ‚·‚é
	for (auto& hasPiece : _mHasPieces) {
		hasPiece.second.erase(nullptr);
	}

	// _vHasPieces‚Ì’†g‚ª‹ó‚È‚ç‰½‚à‚µ‚È‚¢
	if(_vHasPieces.empty()) return false;

	for(auto& piece : _vHasPieces) {
		auto kType = piece->GetPieceType();
		switch (kType) 
		{
			case PIECE_TYPE::kPawn:
				piece->SetPos(_vSquares[0]->GetCenterPos());
				_mHasPieces[HAS_PIECE_TYPE::Pawn].emplace(piece);
				break;

			case PIECE_TYPE::kLance:
				piece->SetPos(_vSquares[1]->GetCenterPos());
				_mHasPieces[HAS_PIECE_TYPE::Lance].emplace(piece);
				break;

			case PIECE_TYPE::kKnight:
				piece->SetPos(_vSquares[2]->GetCenterPos());
				_mHasPieces[HAS_PIECE_TYPE::Knight].emplace(piece);
				break;

			case PIECE_TYPE::kSilver:
				piece->SetPos(_vSquares[3]->GetCenterPos());
				_mHasPieces[HAS_PIECE_TYPE::Silver].emplace(piece);
				break;

			case PIECE_TYPE::kGold:
				piece->SetPos(_vSquares[4]->GetCenterPos());
				_mHasPieces[HAS_PIECE_TYPE::Gold].emplace(piece);
				break;

			case PIECE_TYPE::kBishop:
				piece->SetPos(_vSquares[5]->GetCenterPos());
				_mHasPieces[HAS_PIECE_TYPE::Bishop].emplace(piece);
				break;

			case PIECE_TYPE::kRook:
				piece->SetPos(_vSquares[6]->GetCenterPos());
				_mHasPieces[HAS_PIECE_TYPE::Rook].emplace(piece);
				break;
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

Piece* PieceStand::GetMPiece(HAS_PIECE_TYPE type)
{
	auto itr = _mHasPieces.find(type);
	if (itr != _mHasPieces.end()) {
		auto piece = *itr->second.begin();
		return piece;
	}
	return nullptr;
}
