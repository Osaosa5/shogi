
#include "PieceStand.h"
#include "Square.h"

PieceStand::PieceStand(ObjectManager* objManajer, VECTOR pos, std::string player)
{
	_objManager = objManajer;
	_pos = pos;

	if(player == "player1")			_kPlayerType = PLAYER_TYPE::Player1;
	else if(player == "player2")	_kPlayerType = PLAYER_TYPE::Player2;

	_handle = RM::MV1LoadModel("res/3D/将棋の駒台.mv1");

	// マスの追加
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
			dan = 1; suji = 0;
			break;
		case 2:
			posSquare = VGet(_pos.x + SQUARE_WIDTH - x, _pos.y + y, _pos.z + z);
			dan = 2; suji = 0;
			break;
		case 3:
			posSquare = VGet(_pos.x - SQUARE_WIDTH - x, _pos.y + y, _pos.z - SQUARE_HEIGHT + z);
			dan = 0; suji = 1;
			break;
		case 4:
			posSquare = VGet(_pos.x - x, _pos.y + y, _pos.z - SQUARE_HEIGHT + z);
			dan = 1; suji = 1;
			break;
		case 5:
			posSquare = VGet(_pos.x + SQUARE_WIDTH - x, _pos.y + y, _pos.z - SQUARE_HEIGHT + z);
			dan = 2; suji = 1;
			break;
		case 6:
			posSquare = VGet(_pos.x - SQUARE_WIDTH - x, _pos.y + y, _pos.z - SQUARE_HEIGHT * 2 + z);
			dan = 0; suji = 2;
			break;
		}
		
		_vSquares.emplace_back(new Square(posSquare, player, dan, suji));
		std::string name = "StandSquare" + std::to_string(i);
		_objManager->Add(_vSquares[i], name.c_str());
	}
}

PieceStand::~PieceStand()
{
	//_vHasPieces.clear();
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
	// _mHasPiecesに_kOwnerTypeがBoardの駒があれば削除する
	for (auto& hasPiece : _mHasPieces) {
		for (auto it = hasPiece.second.begin(); it != hasPiece.second.end(); ) {
			if ((*it)->GetOwnerType() == Piece::OWNER_TYPE::Board) {
				it = hasPiece.second.erase(it);  // イテレータを無効にしないように削除
			}
			else {
				++it;
			}
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

void PieceStand::AddPiece(Piece* piece)
{
	auto kType = piece->GetPieceType();
	switch (kType) {
	case PIECE_TYPE::Pawn:
		piece->SetDan(_vSquares[0]->GetDan());
		piece->SetSuji(_vSquares[0]->GetSuji());
		_mHasPieces[HAS_PIECE_TYPE::Pawn].emplace(piece);
		break;

	case PIECE_TYPE::Lance:
		piece->SetDan(_vSquares[1]->GetDan());
		piece->SetSuji(_vSquares[1]->GetSuji());
		_mHasPieces[HAS_PIECE_TYPE::Lance].emplace(piece);
		break;

	case PIECE_TYPE::Knight:
		piece->SetDan(_vSquares[2]->GetDan());
		piece->SetSuji(_vSquares[2]->GetSuji());
		_mHasPieces[HAS_PIECE_TYPE::Knight].emplace(piece);
		break;

	case PIECE_TYPE::Silver:
		piece->SetDan(_vSquares[3]->GetDan());
		piece->SetSuji(_vSquares[3]->GetSuji());
		_mHasPieces[HAS_PIECE_TYPE::Silver].emplace(piece);
		break;

	case PIECE_TYPE::Gold:
		piece->SetDan(_vSquares[4]->GetDan());
		piece->SetSuji(_vSquares[4]->GetSuji());
		_mHasPieces[HAS_PIECE_TYPE::Gold].emplace(piece);
		break;

	case PIECE_TYPE::Bishop:
		piece->SetDan(_vSquares[5]->GetDan());
		piece->SetSuji(_vSquares[5]->GetSuji());
		_mHasPieces[HAS_PIECE_TYPE::Bishop].emplace(piece);
		break;

	case PIECE_TYPE::Rook:
		piece->SetDan(_vSquares[6]->GetDan());
		piece->SetSuji(_vSquares[6]->GetSuji());
		_mHasPieces[HAS_PIECE_TYPE::Rook].emplace(piece);
		break;
	}
}

void PieceStand::RemovePiece(Piece* piece)
{
	auto kType = piece->GetPieceType();
	switch (kType) {
	case PIECE_TYPE::Pawn:
		_mHasPieces[HAS_PIECE_TYPE::Pawn].erase(piece);
		break;

	case PIECE_TYPE::Lance:
		_mHasPieces[HAS_PIECE_TYPE::Lance].erase(piece);
		break;

	case PIECE_TYPE::Knight:
		_mHasPieces[HAS_PIECE_TYPE::Knight].erase(piece);
		break;

	case PIECE_TYPE::Silver:
		_mHasPieces[HAS_PIECE_TYPE::Silver].erase(piece);
		break;

	case PIECE_TYPE::Gold:
		_mHasPieces[HAS_PIECE_TYPE::Gold].erase(piece);
		break;

	case PIECE_TYPE::Bishop:
		_mHasPieces[HAS_PIECE_TYPE::Bishop].erase(piece);
		break;

	case PIECE_TYPE::Rook:
		_mHasPieces[HAS_PIECE_TYPE::Rook].erase(piece);
		break;
	}
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

Piece* PieceStand::GetMPiece(PIECE_TYPE type)
{
	std::unordered_map<PIECE_TYPE, HAS_PIECE_TYPE> pieceTypeMap =
	{
		{PIECE_TYPE::Pawn,		HAS_PIECE_TYPE::Pawn},
		{PIECE_TYPE::Lance,		HAS_PIECE_TYPE::Lance},
		{PIECE_TYPE::Knight,	HAS_PIECE_TYPE::Knight},
		{PIECE_TYPE::Silver,	HAS_PIECE_TYPE::Silver},
		{PIECE_TYPE::Gold,		HAS_PIECE_TYPE::Gold},
		{PIECE_TYPE::Bishop,	HAS_PIECE_TYPE::Bishop},
		{PIECE_TYPE::Rook,		HAS_PIECE_TYPE::Rook}
	};

	auto it = pieceTypeMap.find(type);
	if (it != pieceTypeMap.end()) {
		auto piece = GetMPiece(it->second);
		return piece;
	}

	return nullptr;
}

void PieceStand::SetMPiece(Piece* piece)
{
	// first: 取得した駒の種類, second: 駒台に置く駒の種類
	// Shogiクラスで定義したタイプとPieceStandクラスで定義したタイプだと、
	// int型の値が異なるため、unordered_mapを使って対応させる
	std::unordered_map<PIECE_TYPE, HAS_PIECE_TYPE> pieceTypeMap = 
	{
		{PIECE_TYPE::Pawn,		HAS_PIECE_TYPE::Pawn},
		{PIECE_TYPE::Lance,		HAS_PIECE_TYPE::Lance},
		{PIECE_TYPE::Knight,	HAS_PIECE_TYPE::Knight},
		{PIECE_TYPE::Silver,	HAS_PIECE_TYPE::Silver},
		{PIECE_TYPE::Gold,		HAS_PIECE_TYPE::Gold},
		{PIECE_TYPE::Bishop,	HAS_PIECE_TYPE::Bishop},
		{PIECE_TYPE::Rook,		HAS_PIECE_TYPE::Rook}
	};

	auto kType	= piece->GetPieceType();
	auto it		= pieceTypeMap.find(kType);
	if (it != pieceTypeMap.end()) {
		_mHasPieces[it->second].emplace(piece);
	}
}
