#pragma once

#include "Shogi.h"
#include "ObjectManager.h"
#include "Piece.h"
#include "ModeGame.h"

class Player : public Shogi
{
	using SquarePos = std::pair<int, int>;
public:
	Player(ObjectManager* objManeger, std::string player, ModeGame* game);
	~Player();

	bool Initialize()	override;
	bool Terminate()	override;
	bool Process()		override;
	bool Render()		override;

	void SelectSquare(int trg);	

	// 将棋盤と駒台、それぞれのマスを選択する処理
	void SelectBoardSquare(int index);
	void SelectPieceStandSquare(int index);

	// 将棋盤と駒台、どちらのマスを選択しているかを切り替える処理
	void ChangeSelectBoardToStand();
	void ChangeSelectDestinationBoard();
	void ChangeSelectStandToBoard();
	void ChangeSelectDestinationStandToBoard();

	// 将棋盤の駒を動かす処理
	void	SelectBoardPiece(int index);
	void	MoveBoardPiece(int index);
	Piece*	TakePiece(Piece* ptrPiece);

	// 駒台の駒を動かす処理
	void SelectStandPiece(int index);
	void MoveStandPiece(int index);

	enum class PLAYER_STATE
	{
		BoardSquare,			// 将棋盤にある動かしたい駒を選択中
		DestBoardSquare,		// 将棋盤にある駒の移動先を選択中
		PieceStandSquare,		// 駒台にある動かしたい駒を選択中
		DestPieceStandSquare,	// 駒台にある駒の移動先を選択中
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
	SquarePos	_selectSquareBoard;
	SquarePos	_selectSquareStand;

	// プレイヤーの状態
	PLAYER_STATE	_state;
	bool			_isSelectPieceOfPieceStand;
};

