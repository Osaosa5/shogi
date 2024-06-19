
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
	_vBoardTiles = board["map"].get<std::vector<int>>();

	// �}�X��ǉ�
	for(int y = 0; y < SUJI_MAX; y++) {
		for(int x = 0; x < DAN_MAX; x++) {
			// �}�X��x������3.5f�Az������3.85f�����炵�Ĕz�u
			float w = 3.53f; float h = 3.87f;
			VECTOR pos = VGet(-15.88f + w * x, 21, 13.55f - h * y);
			std::pair<float, float> size = std::make_pair(w - 0.01f, h - 0.01f);

			// �{�[�h�̃^�C����������o��
			int boardTile = _vBoardTiles[y * DAN_MAX + x];

			// �ǉ�����^�C�����N�̐w�n�Ȃ̂��𔻒肷��
			// y��0~2�s�ڂ�player2�A3~5�s�ڂ͒����A6~8�s�ڂ�player1
			std::string player;
			if(y < 3) player = "player2";
			else if(y > 5) player = "player1";
			else player = "";

			std::string name = "square" + std::to_string(x + y * DAN_MAX);
			objManeger->Add(new Square(objManeger, pos, size, boardTile, player, x, y), name.c_str());
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
