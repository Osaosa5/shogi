
#include "Square.h"

Square::Square(VECTOR pos, std::pair<float, float> size, int mapChip, std::string area)
{
	_pos = pos;
	_size = size;

	// Squareの中心座標を計算
	VECTOR vec = VAdd(_pos, VGet(_size.first, 0, _size.second));
	_center = VGet((_pos.x + vec.x) / 2, _pos.y, (_pos.z + vec.z) / 2);

	// マップチップの種類を設定
	_mapChip = mapChip;
	if (!_mapChip) _komaType = (KOMA_TYPE)_mapChip;

	// エリアの種類を設定
	if (area == "player1") _areaType = AREA_TYPE::kPlayer1Area;
	else if (area == "player2") _areaType = AREA_TYPE::kPlayer2Area;
	else _areaType = AREA_TYPE::kNeutral;
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
	return true;
}

bool Square::Render()
{
	std::map<std::string, VECTOR> box;
	box["lUp"] = _pos;
	box["lBottom"] = VGet(_pos.x, _pos.y, _pos.z + _size.second);
	box["rUp"] = VGet(_pos.x + _size.first, _pos.y, _pos.z);
	box["rBottom"] = VGet(_pos.x + _size.first, _pos.y, _pos.z + _size.second);
	DrawTriangle3D(box["lUp"], box["lBottom"], box["rBottom"], GetColor(0, 0, 255), FALSE);
	DrawTriangle3D(box["lUp"], box["rUp"], box["rBottom"], GetColor(0, 0, 255), FALSE);
		
	// Squareの中心座標を表示
	VECTOR localPos = ConvWorldPosToScreenPos(_center);
	DrawFormatString(localPos.x, localPos.y, GetColor(0, 255, 0), "x:%3.1f \nz:%3.1f", _center.x, _center.z);

	return true;
}
