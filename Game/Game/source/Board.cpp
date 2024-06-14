
#include "Board.h"

#include "Square.h"
#include "Fuhyo.h"
#include "Lance.h"
#include "Knight.h"
#include "SilverGeneral.h"
#include "GoldGeneral.h"
#include "King.h"
#include "Bishop.h"
#include "Rook.h"

Board::Board(ObjectManager* objManeger, nlohmann::json board)
{
	_boardChip = board["map"].get<std::vector<int>>();

	// マスを追加
	for(int y = 0; y < 9; y++) {
		for(int x = 0; x < 9; x++) {
			// マスをx方向に3.5f、z方向に3.85fずつずらして配置
			float w = 3.53f; float h = 3.87f;
			VECTOR pos = VGet(-15.88f + w * x, 21, 13.55f - h * y);
			std::pair<float, float> size = std::make_pair(w - 0.01f, h - 0.01f);

			// マスのマップチップを取得
			int boardChip = _boardChip[y * 9 + x];

			// マスの陣地がどちらのプレイヤーのものかを取得
			// 0~2行目はplayer2、3~5行目は中立、6~8行目はplayer1
			std::string player;
			if(y < 3) player = "player2";
			else if(y > 5) player = "player1";
			else player = "";

			std::string name = "square" + std::to_string(x + y * 9);
			objManeger->Add(new Square(pos, size, boardChip, player), name.c_str());
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
