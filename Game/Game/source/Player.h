#pragma once

#include "Shogi.h"
#include "ObjectManager.h"
#include "Piece.h"
#include "ModeGame.h"

class Player : public Shogi
{
	using SelectSquarePos = std::pair<int, int>;
public:
	Player(ObjectManager* objManeger, std::string player, ModeGame* game);
	~Player();

	bool Initialize()	override;
	bool Terminate()	override;
	bool Process()		override;
	bool Render()		override;

	void SelectSquare(int trg);	

	// 将棋盤の駒を動かす処理
	void SelectBoardPiece(int index);
	void MoveBoardPiece(int index);
	Piece* TakePiece(Piece* ptrPiece);

	// 駒台の駒を動かす処理
	void SelectStandPiece(int index);
	void MoveStandPiece(int index);

	void ChangeSelectBoardToStand();
	void ChangeSelectStandToBoard();

	void SelectBoardSquare(int index);
	void SelectPieceStandSquare(int index);

	enum class PLAYER_STATE
	{
		SelectBoardSquare,
		SelectPieceStandSquare
	};

	PLAYER_STATE	GetState()const					{ return _state; }
	void			SetState(PLAYER_STATE state)	{ _state = state; }

private:
	// 参照するクラスのポインタ
	ObjectManager*	_objManager;
	ModeGame*		_game;

	// 選択している駒のインデックス
	int				_selectedPieceIndex;

	// 選択しているマスの座標
	// first : 段(int), second : 筋(int)
	SelectSquarePos	_selectSquareBoard;
	SelectSquarePos	_selectSquareStand;

	// プレイヤーの状態
	PLAYER_STATE	_state;
	bool			_isSelectPieceOfPieceStand;
};

