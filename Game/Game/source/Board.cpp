#include "Board.h"

Board::Board(ObjectManager* objManager)
{
	_ptrObjManager = objManager;

	// 将棋盤の升目の情報を追加
	nlohmann::json		j			= JsonManeger::LoadJsonFile("JSON/board.json");
	std::vector<int>	vBoardTiles = j["map"].get<std::vector<int>>();

	_vHasSquares.resize(BOARD_TILE);  // 9x9のマスを生成
	_vHasPieces.resize(BOARD_TILE);   // 9x9の駒のベクターを生成

	// マスを追加 9x9のマスを生成
	for (int y = 0; y < BOARD_SIZE; y++) {
		for (int x = 0; x < BOARD_SIZE; x++) {
			// マスをx方向に3.5f、z方向に3.85fずつずらして配置
			VECTOR pos = VGet(-15.87f + SQUARE_WIDTH * x, 21.f, 13.54f - SQUARE_HEIGHT * y);

			// ボードのタイル情報を一つ取り出す
			int boardTile = vBoardTiles[y * BOARD_SIZE + x];

			// 追加するタイルが誰の陣地なのかを判定する
			// yが0~2行目はplayer2、3~5行目は中立、6~8行目はplayer1
			std::string strPlayer;
			if (y < 3)		strPlayer = "player2";
			else if (y > 5) strPlayer = "player1";
			else			strPlayer = "";

			// 将棋盤の升目を追加
			int			index	= y * BOARD_SIZE + x;
			std::string name	= "square" + std::to_string(index);
			_vHasSquares[index] = new Square(pos, strPlayer, x, y);

			// オブジェクトマネージャに追加
			_ptrObjManager->Add(_vHasSquares[index], name.c_str());

			// 駒を追加
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
		case PIECE_TYPE::Pawn:
			baseName = "Pawn";
			strPawn = baseName + std::to_string(pawn);
			_ptrObjManager->Add(piece, strPawn.c_str());
			pawn++;
			break;
		case PIECE_TYPE::Lance:
			baseName = "Lance";
			strLance = baseName + std::to_string(lance);
			_ptrObjManager->Add(piece, strLance.c_str());
			lance++;
			break;
		case PIECE_TYPE::Knight:
			baseName = "Knight";
			strKnight = baseName + std::to_string(knight);
			_ptrObjManager->Add(piece, strKnight.c_str());
			knight++;
			break;
		case PIECE_TYPE::Silver:
			baseName = "Silver";
			strSilver = baseName + std::to_string(silver);
			_ptrObjManager->Add(piece, strSilver.c_str());
			silver++;
			break;
		case PIECE_TYPE::Gold:
			baseName = "Gold";
			strGold = baseName + std::to_string(gold);
			_ptrObjManager->Add(piece, strGold.c_str());
			gold++;
			break;
		case PIECE_TYPE::Bishop:
			baseName = "Bishop";
			strBishop = baseName + std::to_string(bishop);
			_ptrObjManager->Add(piece, strBishop.c_str());
			bishop++;
			break;
		case PIECE_TYPE::Rook:
			baseName = "Rook";
			strRook = baseName + std::to_string(rook);
			_ptrObjManager->Add(piece, strRook.c_str());
			rook++;
			break;
		case PIECE_TYPE::King:
			baseName = "King";
			strKing = baseName + std::to_string(king);
			_ptrObjManager->Add(piece, strKing.c_str());
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
	switch (tile) {
		case 0:
			_vHasPieces[index] = nullptr; break;
		case 1:
			_vHasPieces[index] = new Pawn(_ptrObjManager, dan, suji, strPlayer); break;
		case 2:
			_vHasPieces[index] = new Lance(_ptrObjManager, dan, suji, strPlayer); break;
		case 3:
			_vHasPieces[index] = new Knight(_ptrObjManager, dan, suji, strPlayer); break;
		case 4:
			_vHasPieces[index] = new Silver(_ptrObjManager, dan, suji, strPlayer); break;
		case 5:
			_vHasPieces[index] = new Gold(_ptrObjManager, dan, suji, strPlayer); break;
		case 6:
			_vHasPieces[index] = new Bishop(_ptrObjManager, dan, suji, strPlayer); break;
		case 7:
			_vHasPieces[index] = nullptr; break;
		case 8:
			_vHasPieces[index] = new Rook(_ptrObjManager, dan, suji, strPlayer); break;
		case 9:
			_vHasPieces[index] = nullptr; break;
		case 10:
			_vHasPieces[index] = new King(_ptrObjManager, dan, suji, strPlayer); break;
	}
}
