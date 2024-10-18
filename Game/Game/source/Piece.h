#pragma once

#include "Shogi.h"

#include "ObjectManager.h"
#include "Square.h"

class Piece : public Shogi
{
public:
	Piece(ObjectManager* objManajer, int dan, int suji, std::string strPlayer);
	virtual ~Piece();

	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

public:
	/**
	* @enum 	OWNER_TYPE
	* 駒を所有し、管理しているオブジェクトの種類
	*/
	enum class OWNER_TYPE 
	{
		//! 駒は盤上にある
		Board,
		//! 駒は駒台の上にある
		PieceStand
	};

	/**
	* @enum 	PIECE_STATE
	* 駒の状態
	*/
	enum class PIECE_STATE
	{
		//! 駒は何もされていない
		None,
		//! 駒が選択されている
		Select,
		//! 駒が移動している
		Move
	};

public:
	/**
	* @brief		None時の処理
	* @return		処理が成功したかどうか
	*/
	bool NoneProcess();

	/**
	* @brief		Select時の処理
	* @return		処理が成功したかどうか
	*/
	bool SelectProcess();

	/**
	* @brief		Move時の処理
	* @return		処理が成功したかどうか
	*/
	bool MoveProcess();


	/**
	* @brief		コマの移動先がどこか調べる
	* @param[in]	index		コマのインデックス
	* @param[in]	row			行
	* @param[in]	col			列
	* @return		移動先がどこか 正確には配列のインデックス
	*/
	int		CheckDest(int index, int row, int col);

	/**
	* @brief		コマが移動可能なマスの数を調べる
	* @param[in]	row			行
	* @param[in]	col			列
	* @return		移動可能なマスの数
	*/
	int		CheckCntMovable(int row, int col);

	/**
	* @brief		コマが移動可能かを調べる
	* @param[in]	index		コマのインデックス
	* @return		移動可能かどうか
	*				true: 移動可 false: 移動不可
	*/
	bool	IsMove(int index);

	/**
	* @brief		コマを移動する
	* @param[in]	index		コマのインデックス
	* @return		移動できたかどうか
	* 				true: 移動可 false: 移動不可
	*/
	bool Move(int index);

	/**
	* @brief		コマをマスの中央に置く
	*/
	void PutPieceCentralTile();

	/**
	* @brief		プレイヤーの方向を更新する
	* @param[in]	playerType		プレイヤーの種類
	* @detail		プレイヤーの種類によって、駒が向く方向が異なる
	*/
	void UpdateDirectionForPlayer(PLAYER_TYPE playerType);

	// ゲッター
	/**
	* @brief		3D座標の更新フラグを取得する
	* @return		3D座標の更新フラグ
	* @detail		trueの場合、駒がマスの中央に置かれる
	*/
	bool GetUpdate3DPos() const	{ return _bUpdate3DPos; }

	/**
	* @brief		駒の所有者を取得する
	* @return		所有者
	*				Board:駒は盤上にある
	*				PieceStand:駒は駒台の上にある
	*/
	OWNER_TYPE			GetOwnerType() const	{ return _kOwnerType; }

	/**
	* @brief		駒の移動範囲を取得する
	* @return		駒の移動範囲(vector)
	* @detail		移動範囲は駒の種類によって異なる
	*				17*17の配列で表現される
	*/
	std::vector<int>	GetMoveRange() const	{ return _vMoveRange; }

	/**
	* @brief		駒の状態を取得する
	* @return		駒の状態
	* 				None: 駒は何もされていない
	* 				Select: 駒が選択されている
	* 				Move: 駒が移動している
	*/
	PIECE_STATE			GetPieceState() const { return _kPieceState; }

	// セッター
	/**
	* @brief		3D座標の更新フラグを設定する
	* @param[in]	bUpdate3DPos	3D座標の更新フラグ
	* @detail		trueの場合、駒がマスの中央に置かれる
	*/
	void SetUpdate3DPos(bool bUpdate3DPos)	{ _bUpdate3DPos = bUpdate3DPos; }

	/**
	* @brief		駒の所有者を設定する
	* @param[in]	ownerType		所有者
	* 				Board:駒は盤上にある
	* 				PieceStand:駒は駒台の上にある
	*/
	void SetOwnerType(OWNER_TYPE ownerType)	{ _kOwnerType = ownerType; }

	/**
	* @beief		駒の状態を設定する
	* @param[in]	pieceState		駒の状態
	* 				None: 駒は何もされていない
	* 				Select: 駒が選択されている
	* 				Move: 駒が移動している
	*/
	void SetPieceState(PIECE_STATE pieceState) { _kPieceState = pieceState; }

protected:
	bool				_bUpdate3DPos;	//! 3D座標の更新フラグ
	OWNER_TYPE			_kOwnerType;	//! 駒の所有者
	std::vector<int>	_vMoveRange;	//! 駒の移動範囲
	PIECE_STATE			_kPieceState;	//! 駒の状態

private:
	ObjectManager* _objManager;	//! オブジェクトマネージャ	アグリゲーションの関係にある
};

