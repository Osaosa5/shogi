
#include "Square.h"
#include "Object.h"

Square::Square(VECTOR pos, std::string area, int dan, int suji)
{
	_pos = pos;
	_size = std::make_pair(SQUARE_WIDTH, SQUARE_HEIGHT);

	// Squareの中心座標を計算
	VECTOR vec = VAdd(_pos, VGet(_size.first, 0, _size.second));
	_center = VGet((_pos.x + vec.x) / 2, _pos.y, (_pos.z + vec.z) / 2);

	_bSelect = false;

	// エリアの種類を設定
	if (area == "player1") _kAreaType = AREA_TYPE::Player1Area;
	else if (area == "player2") _kAreaType = AREA_TYPE::Player2Area;
	else _kAreaType = AREA_TYPE::Neutral;

	// 縦の列と横の行を設定
	_dan = dan; _suji = suji;

	// マスの色を設定
	_cr = 0;

	// マスの状態を設定
	_kSquareState = SQUARE_STATE::None;
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
	// マスの状態を更新
	if (_kSquareState == SQUARE_STATE::Placeable)
	{
		// 駒を置けるマスは黄緑色
		_cr = GetColor(173, 255, 47);
	}
	else if (_kSquareState == SQUARE_STATE::NotPlaceable)
	{
		// 駒を置けないマスは赤色
		_cr = GetColor(255, 0, 0);
	}

	return true;
}

bool Square::Render()
{
	//if (!_bSelect && _kSquareState == SQUARE_STATE::None) return false;

	// マスの四隅の座標を計算
	std::unordered_map<std::string, VECTOR> box;
	box["lUp"]		= _pos;
	box["lBottom"]	= VGet(_pos.x, _pos.y, _pos.z + _size.second);
	box["rUp"]		= VGet(_pos.x + _size.first, _pos.y, _pos.z);
	box["rBottom"]	= VGet(_pos.x + _size.first, _pos.y, _pos.z + _size.second);

	// マスの状態によって描画する色を変える
	if (_kSquareState == SQUARE_STATE::Placeable || _kSquareState == SQUARE_STATE::NotPlaceable)
	{
		// マスを描画
		DrawTriangle3D(box["lUp"], box["lBottom"],	box["rBottom"], _cr, TRUE);
		DrawTriangle3D(box["lUp"], box["rUp"],		box["rBottom"], _cr, TRUE);

		_kSquareState = SQUARE_STATE::None;

		return true;
	}

	int Cr = _bSelect ? GetColor(0, 255, 0) : GetColor(0, 0, 255);

	// マスを描画
	// 選ばれているなら緑色、選ばれていないなら青色
	DrawTriangle3D(box["lUp"], box["lBottom"],	box["rBottom"], Cr, _bSelect);
	DrawTriangle3D(box["lUp"], box["rUp"],		box["rBottom"], Cr, _bSelect);
	
	return true;
}

