
#include "Square.h"
#include "Object.h"
#include "Board.h"

Square::Square(ObjectManager* objManeger, VECTOR pos, std::pair<float, float> size, int mapChip, std::string area, int dan, int suji)
{
	_objManager = objManeger;
	_pos = pos;
	_size = size;

	// Squareの中心座標を計算
	VECTOR vec = VAdd(_pos, VGet(_size.first, 0, _size.second));
	_center = VGet((_pos.x + vec.x) / 2, _pos.y, (_pos.z + vec.z) / 2);

	_bSelect = false;

	// マップチップの種類を設定
	_tile = mapChip;
	if (!_tile) _komaType = (KOMA_TYPE)_tile;
	else _komaType = KOMA_TYPE::kNoneKoma;

	// エリアの種類を設定
	if (area == "player1") _areaType = AREA_TYPE::kPlayer1Area;
	else if (area == "player2") _areaType = AREA_TYPE::kPlayer2Area;
	else _areaType = AREA_TYPE::kNeutral;

	// 縦の列と横の行を設定
	_dan = dan; _suji = suji;
}

Square::~Square()
{
}

bool Square::Terminate()
{
	return true;
}

bool Square::Process()
{
	_komaType = GetKomaAt();
	return true;
}

bool Square::Render()
{
	int Cr = _bSelect ? GetColor(0, 255, 0) : GetColor(0, 0, 255);

	std::unordered_map<std::string, VECTOR> box;
	box["lUp"] = _pos;
	box["lBottom"] = VGet(_pos.x, _pos.y, _pos.z + _size.second);
	box["rUp"] = VGet(_pos.x + _size.first, _pos.y, _pos.z);
	box["rBottom"] = VGet(_pos.x + _size.first, _pos.y, _pos.z + _size.second);
	DrawTriangle3D(box["lUp"], box["lBottom"], box["rBottom"], Cr, _bSelect);
	DrawTriangle3D(box["lUp"], box["rUp"], box["rBottom"], Cr, _bSelect);
	
	return true;
}

Shogi::KOMA_TYPE Square::GetKomaAt()
{
	// ボードの情報を取得
	Object* obj = _objManager->Get("board");
	Board* board = nullptr;
	if (obj) board = dynamic_cast<Board*>(obj);

	// ボードのタイル情報を取得
	std::vector tiles = board->GetBoardTiles();
	if(tiles[_suji * DAN_MAX + _dan]) return (KOMA_TYPE)tiles[_suji * DAN_MAX + _dan];
	else return KOMA_TYPE::kNoneKoma;
}
