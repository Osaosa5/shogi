#include "Board.h"

Board::Board(ObjectManager* objManager)
{
	_objManager = objManager;

	// 将棋盤の升目の情報を追加
	nlohmann::json j = JsonManeger::LoadJsonFile("JSON/board.json");
	std::vector<int> vBoardTiles = j["map"].get<std::vector<int>>();

	// マスを追加 9x9のマスを生成
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			// マスをx方向に3.5f、z方向に3.85fずつずらして配置
			float w = 3.53f; float h = 3.87f;
			VECTOR pos = VGet(-15.88f + w * x, 21, 13.55f - h * y);
			std::pair<float, float> size = std::make_pair(w - 0.01f, h - 0.01f);

			// ボードのタイル情報を一つ取り出す
			int boardTile = vBoardTiles[y * 9 + x];

			// 追加するタイルが誰の陣地なのかを判定する
			// yが0~2行目はplayer2、3~5行目は中立、6~8行目はplayer1
			std::string player;
			if (y < 3) player = "player2";
			else if (y > 5) player = "player1";
			else player = "";

			std::string name = "square" + std::to_string(x + y * 9);
			_squares[y * BOARD_SIZE + x] = new Square(pos, size, player, x, y);
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


	for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
		_squares[i]->Process();
	}
	return true;
}

bool Board::Render()
{
	for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
		_squares[i]->Render();
	}
	return true;
}
