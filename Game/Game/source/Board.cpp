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
			float w = 3.52f; float h = 3.86f;
			VECTOR pos = VGet(-15.87f + w * x, 21, 13.54f - h * y);
			std::pair<float, float> size = std::make_pair(w, h);

			// �{�[�h�̃^�C����������o��
			int boardTile = vBoardTiles[y * 9 + x];

			// �ǉ�����^�C�����N�̐w�n�Ȃ̂��𔻒肷��
			// y��0~2�s�ڂ�player2�A3~5�s�ڂ͒����A6~8�s�ڂ�player1
			std::string strPlayer;
			if (y < 3) strPlayer = "player2";
			else if (y > 5) strPlayer = "player1";
			else strPlayer = "";

			int index = y * BOARD_SIZE + x;
			std::string name = "square" + std::to_string(index);
			_squares[index] = new Square(pos, size, strPlayer, x, y);
			InitPiece(index, boardTile, x, y, strPlayer);
		}
	}

}

Board::~Board()
{
}

bool Board::Terminate()
{
	for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
		_squares[i]->Terminate();
		if (_pieces[i] != nullptr) _pieces[i]->Terminate();
	}
	return true;
}

bool Board::Process()
{


	for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
		_squares[i]->Process();
		if (_pieces[i] != nullptr) _pieces[i]->Process();
	}
	return true;
}

bool Board::Render()
{
	for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
		_squares[i]->Render();
		if (_pieces[i] != nullptr) _pieces[i]->Render();
	}
	return true;
}

void Board::InitPiece(int element, int tile, int dan, int suji, std::string strPlayer)
{
	switch(tile) {
		case 0:
			_pieces[element] = nullptr; break;
		case 1:
			_pieces[element] = new Pawn(_objManager, dan, suji, strPlayer); break;
		case 2:
			_pieces[element] = new Lance(_objManager, dan, suji, strPlayer); break;
		case 3:
			_pieces[element] = new Knight(_objManager, dan, suji, strPlayer); break;
		case 4:
			_pieces[element] = new Silver(_objManager, dan, suji, strPlayer); break;
		case 5:
			_pieces[element] = new Gold(_objManager, dan, suji, strPlayer); break;
		case 6:
			_pieces[element] = new Bishop(_objManager, dan, suji, strPlayer); break;
		case 7:
			_pieces[element] = nullptr; break;
		case 8:
			_pieces[element] = new Rook(_objManager, dan, suji, strPlayer); break;
		case 9:
			_pieces[element] = nullptr; break;
		case 10:
			_pieces[element] = new King(_objManager, dan, suji, strPlayer); break;
	}
}
