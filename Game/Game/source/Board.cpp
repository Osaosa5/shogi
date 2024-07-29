#include "Board.h"

Board::Board(ObjectManager* objManager)
{
	_objManager = objManager;

	// �����Ղ̏��ڂ̏���ǉ�
	nlohmann::json		j			= JsonManeger::LoadJsonFile("JSON/board.json");
	std::vector<int>	vBoardTiles = j["map"].get<std::vector<int>>();

	// �}�X��ǉ� 9x9�̃}�X�𐶐�
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			// �}�X��x������3.5f�Az������3.85f�����炵�Ĕz�u
			VECTOR pos = VGet(-15.87f + SQUARE_WIDTH * x, 21.f, 13.54f - SQUARE_HEIGHT * y);

			// �{�[�h�̃^�C����������o��
			int boardTile = vBoardTiles[y * 9 + x];

			// �ǉ�����^�C�����N�̐w�n�Ȃ̂��𔻒肷��
			// y��0~2�s�ڂ�player2�A3~5�s�ڂ͒����A6~8�s�ڂ�player1
			std::string strPlayer;
			if (y < 3)		strPlayer = "player2";
			else if (y > 5) strPlayer = "player1";
			else			strPlayer = "";

			// �����Ղ̏��ڂ�ǉ�
			int			index	= y * BOARD_SIZE + x;
			std::string name	= "square" + std::to_string(index);
			_vHasSquares.emplace_back(new Square(pos, strPlayer, x, y));

			// �I�u�W�F�N�g�}�l�[�W���ɒǉ�
			_objManager->Add(_vHasSquares[index], name.c_str());

			// ���ǉ�
			InitPiece(index, boardTile, x, y, strPlayer);
		}
	}
	int pawn = 1;
	int lance = 1;
	int knight = 1;
	int silver = 1;
	int gold = 1;
	int bishop = 1;
	int rook = 1;
	int king = 1;

	for (auto& piece : _vHasPieces) {
		if (piece == nullptr) continue;

		PIECE_TYPE type = piece->GetPieceType();
		std::string baseName;
		std::string strPawn;
		std::string strLance;
		std::string strKnight;
		std::string strSilver;
		std::string strGold;
		std::string strBishop;
		std::string strRook;
		std::string strKing;
		switch (type)
		{
		case PIECE_TYPE::kPawn:
			baseName = "Pawn";
			strPawn = baseName + std::to_string(pawn);
			_objManager->Add(piece, strPawn.c_str());
			pawn++;
			break;
		case PIECE_TYPE::kLance:
			baseName = "Lance";
			strLance = baseName + std::to_string(lance);
			_objManager->Add(piece, strLance.c_str());
			lance++;
			break;
		case PIECE_TYPE::kKnight:
			baseName = "Knight";
			strKnight = baseName + std::to_string(knight);
			_objManager->Add(piece, strKnight.c_str());
			knight++;
			break;
		case PIECE_TYPE::kSilver:
			baseName = "Silver";
			strSilver = baseName + std::to_string(silver);
			_objManager->Add(piece, strSilver.c_str());
			silver++;
			break;
		case PIECE_TYPE::kGold:
			baseName = "Gold";
			strGold = baseName + std::to_string(gold);
			_objManager->Add(piece, strGold.c_str());
			gold++;
			break;
		case PIECE_TYPE::kBishop:
			baseName = "Bishop";
			strBishop = baseName + std::to_string(bishop);
			_objManager->Add(piece, strBishop.c_str());
			bishop++;
			break;
		case PIECE_TYPE::kRook:
			baseName = "Rook";
			strRook = baseName + std::to_string(rook);
			_objManager->Add(piece, strRook.c_str());
			rook++;
			break;
		case PIECE_TYPE::kKing:
			baseName = "King";
			strKing = baseName + std::to_string(king);
			_objManager->Add(piece, strKing.c_str());
			king++;
			break;
		}
	}

}

Board::~Board()
{
}

bool Board::Terminate()
{
	
	return true;
}

bool Board::Process()
{

	return true;
}

bool Board::Render()
{
	
	return true;
}

void Board::InitPiece(int index, int tile, int dan, int suji, std::string strPlayer)
{
	switch(tile) {
		case 0:
			_vHasPieces.emplace_back(nullptr); break;
		case 1:
			_vHasPieces.emplace_back(new Pawn(_objManager, dan, suji, strPlayer)); break;
		case 2:
			_vHasPieces.emplace_back(new Lance(_objManager, dan, suji, strPlayer)); break;
		case 3:
			_vHasPieces.emplace_back(new Knight(_objManager, dan, suji, strPlayer)); break;
		case 4:
			_vHasPieces.emplace_back(new Silver(_objManager, dan, suji, strPlayer)); break;
		case 5:
			_vHasPieces.emplace_back(new Gold(_objManager, dan, suji, strPlayer)); break;
		case 6:
			_vHasPieces.emplace_back(new Bishop(_objManager, dan, suji, strPlayer)); break;
		case 7:
			_vHasPieces.emplace_back(nullptr); break;
		case 8:
			_vHasPieces.emplace_back(new Rook(_objManager, dan, suji, strPlayer)); break;
		case 9:
			_vHasPieces.emplace_back(nullptr); break;
		case 10:
			_vHasPieces.emplace_back(new King(_objManager, dan, suji, strPlayer)); break;
	}
}
