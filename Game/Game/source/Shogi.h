#pragma once

#include "Object.h"

class Shogi : public Object
{
public:
	Shogi();
	~Shogi();

	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	enum AREA_TYPE	// エリアの種類
	{
		kNone,		// なし
		kNeutral,	// 中立
		kPlayer1Area,	// Player1
		kPlayer2Area		// Player2
	};

	enum KOMA_TYPE	// 駒の種類
	{
		kNoneKoma,		// なし
		kFuhyo,		// 歩兵
		kKyosha,	// 香車
		kKeima,		// 桂馬
		kGinsho,	// 銀将
		kKinsho,	// 金将
		kHisha,		// 飛車
		kKakugyo,	// 角行
		kOsho,		// 王将
	};

	enum PLAYER_TYPE	// プレイヤーの種類
	{
		kNonePlayer,		// なし
		kPlayer1,	// Player1
		kPlayer2	// Player2
	};

	const int SUJI_MAX = 9;	// 縦の列の最大数
	const int DAN_MAX = 9;	// 横の行の最大数

protected:
	int _suji;	// 縦の列
	int _dan;	// 横の行
	int _elementNum;	// 配列の要素番号
	AREA_TYPE _areaType;	// エリアの種類
	KOMA_TYPE _komaType;	// 駒の種類
	PLAYER_TYPE _playerType;	// プレイヤーの種類
};

