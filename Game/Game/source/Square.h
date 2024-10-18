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
	// マスの状態
	enum class SQUARE_STATE
	{
		None,			// 何もない
		Placeable,		// 駒を置ける
		NotPlaceable	// 駒を置けない
	};

	/**
	* @brief	マスの状態を取得
	* @return	
	* 	None			: 何もない
	* 	Placeable		: 駒を置ける
	* 	NotPlaceable	: 駒を置けない
	*/
	SQUARE_STATE	GetSquareState() const { return _kSquareState; }

	/**
	* @brief	マスの状態を設定
	* @param	state マスの状態
	*		"None"			: 何もない
	* 		"Placeable"		: 駒を置ける
	* 		"NotPlaceable"	: 駒を置けない
	*/
	void			SetSquareState(std::string state)
	{
		if (state == "None")				_kSquareState = SQUARE_STATE::None;
		else if (state == "Placeable")		_kSquareState = SQUARE_STATE::Placeable;
		else if (state == "NotPlaceable")	_kSquareState = SQUARE_STATE::NotPlaceable;
	}

public:
	// マスの大きさを取得
	std::pair<float, float> GetSize() const { return _size; }

	// マスの中心座標を取得
	VECTOR GetCenterPos() const { return _center; }


	bool GetSelect() const			{ return _bSelect; }
	void SetSelect(bool bSelect)	{ _bSelect = bSelect; }

	// マスの種類を取得
	AREA_TYPE GetAreaType() const { return _kAreaType; }

private:
	std::pair<float, float> _size;
	VECTOR					_center;
	bool					_bSelect;
	int						_cr;

	SQUARE_STATE			_kSquareState;	//! マスの状態
};

