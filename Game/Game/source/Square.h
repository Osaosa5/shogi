#pragma once

#include "Shogi.h"
#include "ObjectManager.h"
#include "Piece.h"

class Square : public Shogi
{
public:
	Square(VECTOR pos, std::string player, int dan, int suji);
	~Square();

	bool Terminate() override;
	bool Process() override;
	bool Render() override;

public:
	// �}�X�̏��
	enum class SQUARE_STATE
	{
		None,			// �����Ȃ�
		Placeable,		// ���u����
		NotPlaceable	// ���u���Ȃ�
	};

	/**
	* @brief	�}�X�̏�Ԃ��擾
	* @return	
	* 	None			: �����Ȃ�
	* 	Placeable		: ���u����
	* 	NotPlaceable	: ���u���Ȃ�
	*/
	SQUARE_STATE	GetSquareState() const { return _kSquareState; }

	/**
	* @brief	�}�X�̏�Ԃ�ݒ�
	* @param	state �}�X�̏��
	*		"None"			: �����Ȃ�
	* 		"Placeable"		: ���u����
	* 		"NotPlaceable"	: ���u���Ȃ�
	*/
	void			SetSquareState(std::string state)
	{
		if (state == "None")				_kSquareState = SQUARE_STATE::None;
		else if (state == "Placeable")		_kSquareState = SQUARE_STATE::Placeable;
		else if (state == "NotPlaceable")	_kSquareState = SQUARE_STATE::NotPlaceable;
	}

public:
	// �}�X�̑傫�����擾
	std::pair<float, float> GetSize() const { return _size; }

	// �}�X�̒��S���W���擾
	VECTOR GetCenterPos() const { return _center; }


	bool GetSelect() const			{ return _bSelect; }
	void SetSelect(bool bSelect)	{ _bSelect = bSelect; }

	// �}�X�̎�ނ��擾
	AREA_TYPE GetAreaType() const { return _kAreaType; }

private:
	std::pair<float, float> _size;
	VECTOR					_center;
	bool					_bSelect;
	int						_cr;

	SQUARE_STATE			_kSquareState;	//! �}�X�̏��
};

