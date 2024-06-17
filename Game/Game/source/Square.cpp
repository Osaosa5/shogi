
#include "Square.h"

Square::Square(VECTOR pos, std::pair<float, float> size, int mapChip, std::string area, int dan, int suji)
{
	_pos = pos;
	_size = size;

	// Square�̒��S���W���v�Z
	VECTOR vec = VAdd(_pos, VGet(_size.first, 0, _size.second));
	_center = VGet((_pos.x + vec.x) / 2, _pos.y, (_pos.z + vec.z) / 2);

	// �}�b�v�`�b�v�̎�ނ�ݒ�
	_tile = mapChip;
	if (!_tile) _komaType = (KOMA_TYPE)_tile;

	// �G���A�̎�ނ�ݒ�
	if (area == "player1") _areaType = AREA_TYPE::kPlayer1Area;
	else if (area == "player2") _areaType = AREA_TYPE::kPlayer2Area;
	else _areaType = AREA_TYPE::kNeutral;

	// �c�̗�Ɖ��̍s��ݒ�
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
		
	// Square�̒��S���W��\��
	VECTOR localPos = ConvWorldPosToScreenPos(_center);
	DrawFormatString(localPos.x, localPos.y, GetColor(0, 255, 0), "x:%3.1f \nz:%3.1f", _center.x, _center.z);

	return true;
}
