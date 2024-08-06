#pragma once

#include "Object.h"

constexpr int	BOARD_SIZE		= 9;	
constexpr int	BOARD_TILE		= 81;

constexpr int	PIECESTAND_W	= 3;
constexpr int	PIECESTAND_H	= 3;
constexpr int	PIECESTAND_NUM	= 7;

constexpr float SQUARE_WIDTH	= 3.52f;
constexpr float SQUARE_HEIGHT	= 3.86f;


class Shogi : public Object
{
public:
	Shogi();
	~Shogi();

	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	int		GetDan() const		{ return _dan; }
	void	SetDan(int dan)		{ _dan = dan; }

	int		GetSuji() const		{ return _suji; }
	void	SetSuji(int suji)	{ _suji = suji; }

	int		GetTile() const		{ return _tile; }
	void	SetTile(int tile)	{ _tile = tile; }

	enum class AREA_TYPE	// エリアの種類
	{
		None,			// なし
		Neutral,		// 中立
		Player1Area,	// Player1
		Player2Area	// Player2
	};

	enum class PIECE_TYPE	// 駒の種類
	{
		None,
		Pawn,		// 歩兵
		Lance,		// 香車
		Knight,		// 桂馬
		Silver,		// 銀将
		Gold,		// 金将
		Bishop,		// 角行
		Ryume,		// 龍馬
		Rook,		// 飛車
		Ryuo,		// 竜王
		King,		// 王将
	};

	enum class PLAYER_TYPE	// プレイヤーの種類
	{
		None,	// なし
		Player1,		// Player1
		Player2		// Player2
	};

	AREA_TYPE	GetAreaType() const						{ return _kAreaType; }
	void		SetAreaType(AREA_TYPE areaType)			{ _kAreaType = areaType; }

	PIECE_TYPE	GetPieceType() const					{ return _kPieceType; }
	void		SetPieceType(PIECE_TYPE pieceType)		{ _kPieceType = pieceType; }

	PLAYER_TYPE GetPlayerType() const					{ return _kPlayerType; }
	void		SetPlayerType(PLAYER_TYPE playerType)	{ _kPlayerType = playerType; }

protected:
	int _suji;	// 縦の列
	int _dan;	// 横の行
	int _tile;	// 配列の要素番号

	AREA_TYPE	_kAreaType;		// エリアの種類
	PIECE_TYPE	_kPieceType;	// 駒の種類
	PLAYER_TYPE _kPlayerType;	// プレイヤーの種類
};

