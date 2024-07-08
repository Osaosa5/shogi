#include "Board.h"

Board::Board(ObjectManager* objManager)
{
	_objManager = objManager;

	// �����Ղ̏��ڂ̏���ǉ�
	nlohmann::json j = JsonManeger::LoadJsonFile("JSON/board.json");
	std::vector<int> vBoardTiles = j["map"].get<std::vector<int>>();

	// �}�X��ǉ� 9x9�̃}�X�𐶐�
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			// �}�X��x������3.5f�Az������3.85f�����炵�Ĕz�u
			float w = 3.53f; float h = 3.87f;
			VECTOR pos = VGet(-15.88f + w * x, 21, 13.55f - h * y);
			std::pair<float, float> size = std::make_pair(w - 0.01f, h - 0.01f);

			// �{�[�h�̃^�C����������o��
			int boardTile = vBoardTiles[y * 9 + x];

			// �ǉ�����^�C�����N�̐w�n�Ȃ̂��𔻒肷��
			// y��0~2�s�ڂ�player2�A3~5�s�ڂ͒����A6~8�s�ڂ�player1
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
