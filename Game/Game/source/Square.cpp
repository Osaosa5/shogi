
#include "Square.h"
#include "Object.h"

Square::Square(VECTOR pos, std::string area, int dan, int suji)
{
	_pos = pos;
	_size = std::make_pair(SQUARE_WIDTH, SQUARE_HEIGHT);

	// Square�̒��S���W���v�Z
	VECTOR vec = VAdd(_pos, VGet(_size.first, 0, _size.second));
	_center = VGet((_pos.x + vec.x) / 2, _pos.y, (_pos.z + vec.z) / 2);

	_bSelect = false;

	// �G���A�̎�ނ�ݒ�
	if (area == "player1") _kAreaType = AREA_TYPE::Player1Area;
	else if (area == "player2") _kAreaType = AREA_TYPE::Player2Area;
	else _kAreaType = AREA_TYPE::Neutral;

	// �c�̗�Ɖ��̍s��ݒ�
	_dan = dan; _suji = suji;

	// �}�X�̐F��ݒ�
	_cr = 0;

	// �}�X�̏�Ԃ�ݒ�
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
	// �}�X�̏�Ԃ��X�V
	if (_kSquareState == SQUARE_STATE::Placeable)
	{
		// ���u����}�X�͉��ΐF
		_cr = GetColor(173, 255, 47);
	}
	else if (_kSquareState == SQUARE_STATE::NotPlaceable)
	{
		// ���u���Ȃ��}�X�͐ԐF
		_cr = GetColor(255, 0, 0);
	}

	return true;
}

bool Square::Render()
{
	//if (!_bSelect && _kSquareState == SQUARE_STATE::None) return false;

	// �}�X�̎l���̍��W���v�Z
	std::unordered_map<std::string, VECTOR> box;
	box["lUp"]		= _pos;
	box["lBottom"]	= VGet(_pos.x, _pos.y, _pos.z + _size.second);
	box["rUp"]		= VGet(_pos.x + _size.first, _pos.y, _pos.z);
	box["rBottom"]	= VGet(_pos.x + _size.first, _pos.y, _pos.z + _size.second);

	// �}�X�̏�Ԃɂ���ĕ`�悷��F��ς���
	if (_kSquareState == SQUARE_STATE::Placeable || _kSquareState == SQUARE_STATE::NotPlaceable)
	{
		// �}�X��`��
		DrawTriangle3D(box["lUp"], box["lBottom"],	box["rBottom"], _cr, TRUE);
		DrawTriangle3D(box["lUp"], box["rUp"],		box["rBottom"], _cr, TRUE);

		_kSquareState = SQUARE_STATE::None;

		return true;
	}

	int Cr = _bSelect ? GetColor(0, 255, 0) : GetColor(0, 0, 255);

	// �}�X��`��
	// �I�΂�Ă���Ȃ�ΐF�A�I�΂�Ă��Ȃ��Ȃ�F
	DrawTriangle3D(box["lUp"], box["lBottom"],	box["rBottom"], Cr, _bSelect);
	DrawTriangle3D(box["lUp"], box["rUp"],		box["rBottom"], Cr, _bSelect);
	
	return true;
}

