#pragma once

#include "Object.h"

constexpr int	BOARD_SIZE		= 9;	
constexpr int	BOARD_TILE		= 81;

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

	int GetDan() const { return _dan; }
	void SetDan(int dan) { _dan = dan; }

	int GetSuji() const { return _suji; }
	void SetSuji(int suji) { _suji = suji; }

	int GetTile() const { return _tile; }
	void SetTile(int tile) { _tile = tile; }

	enum AREA_TYPE	// エリアの種類
	{
		kNone,		// なし
		kNeutral,	// 中立
		kPlayer1Area,	// Player1
		kPlayer2Area		// Player2
	};

	enum PIECE_TYPE	// 駒の種類
	{
		kNonePiece,
		kPawn,		// 歩兵
		kLance,		// 香車
		kKnight,	// 桂馬
		kSilver,	// 銀将
		kGold,		// 金将
		kBishop,	// 角行
		kRyume,		// 龍馬
		kRook,		// 飛車
		kRyuo,		// 竜王
		kKing,		// 王将
	};

	enum PLAYER_TYPE	// プレイヤーの種類
	{
		kNonePlayer,		// なし
		kPlayer1,	// Player1
		kPlayer2	// Player2
	};

	AREA_TYPE GetAreaType() const { return _areaType; }
	void SetAreaType(AREA_TYPE areaType) { _areaType = areaType; }

	PIECE_TYPE GetPieceType() const { return _pieceType; }
	void SetPieceType(PIECE_TYPE pieceType) { _pieceType = pieceType; }

	PLAYER_TYPE GetPlayerType() const { return _playerType; }
	void SetPlayerType(PLAYER_TYPE playerType) { _playerType = playerType; }

protected:
	int _suji;	// 縦の列
	int _dan;	// 横の行
	int _tile;	// 配列の要素番号
	AREA_TYPE _areaType;	// エリアの種類
	PIECE_TYPE _pieceType;	// 駒の種類
	PLAYER_TYPE _playerType;	// プレイヤーの種類
};

