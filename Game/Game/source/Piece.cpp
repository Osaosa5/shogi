
#include "Piece.h"

#include "appframe.h"
#include "Board.h"
#include "PieceStand.h"

Piece::Piece(ObjectManager* objManajer, int dan, int suji, std::string strPlayer)
{
	_objManager		= objManajer;
	_bUpdate3DPos	= true;
	_kOwnerType		= OWNER_TYPE::Board;
	_kPieceState	= PIECE_STATE::None;

	// 駒の位置情報
	_dan	= dan; 
	_suji	= suji;
	_tile	= _suji * BOARD_SIZE + _dan;

	// プレイヤー情報
	if (strPlayer == "player1") _kPlayerType = PLAYER_TYPE::Player1;
	if (strPlayer == "player2") _kPlayerType = PLAYER_TYPE::Player2;
	UpdateDirectionForPlayer(_kPlayerType);

	// 駒の移動範囲
	_vMoveRange.resize(MOVE_RANGE_W * MOVE_RANGE_H);
}

Piece::~Piece()
{
}

bool Piece::Terminate()
{
	_vMoveRange.clear();
	return true;
}

bool Piece::Process()
{
	// 駒の状態によって処理が変わる
	switch (_kPieceState)
	{
		// 駒が何もされていない場合
	case PIECE_STATE::None:
		NoneProcess();
		break;
		// 駒が選択されている場合
	case PIECE_STATE::Select:
		SelectProcess();
		break;
		// 駒が移動している場合
	case PIECE_STATE::Move:
		MoveProcess();
		break;
	}

	return true;
}

bool Piece::Render()
{
	// 角度と位置をセットして描画
	MV1SetRotationXYZ(_handle, _rot);
	MV1SetPosition(_handle, _pos);
	MV1DrawModel(_handle);

	return true;
}

bool Piece::NoneProcess()
{
	// 駒のインデックスを更新する
	_tile = _suji * BOARD_SIZE + _dan;

	// 駒の位置を更新する
	if (_bUpdate3DPos)
	{
		// 駒の位置をマスの中央にセットする
		PutPieceCentralTile();

		// 3Dの位置を更新フラグをfalseにする
		_bUpdate3DPos = false;
	}

	// 駒の向きを更新する
	UpdateDirectionForPlayer(_kPlayerType);

	return true;
}

bool Piece::SelectProcess()
{
	// 駒の位置をマスの少し上にずらす
	auto ptrBoard = dynamic_cast<Board*>(_objManager->Get("board"));
	auto ptrSquare = ptrBoard->GetSquare(_tile);
	this->_pos.y = ptrSquare->GetCenterPos().y + 1.f;

	// 移動できるマスを調べる
	if (IsMove(_tile))
	{
		
	}

	return true;
}

bool Piece::MoveProcess()
{
	return true;
}

int Piece::CheckDest(int index, int row, int col)
{
	// 移動範囲の範囲内の場合
	int destRow = index % MOVE_RANGE_W;
	int destCol = index / MOVE_RANGE_H;

	// 中央からの距離を取得
	int distanceRow = destRow - RANGE_CENTRAL_W;
	int distanceCol = destCol - RANGE_CENTRAL_H;

	// 移動先のマスを取得
	return (col + distanceCol) * BOARD_SIZE + (row + distanceRow);
}

int Piece::CheckCntMovable(int row, int col)
{
	int tileIndex	= 0;
	int moveCnt		= 0;
	for (auto move : _vMoveRange)
	{
		// 移動範囲の範囲外の場合はスキップ
		if (move == 0 || move == 11)
		{
			tileIndex++; continue;
		}

		// 移動先のマスを取得
		int destIndex = CheckDest(tileIndex, row, col);

		// 移動先のマスが範囲外の場合はスキップ
		if (destIndex < 0 || destIndex >= BOARD_TILE)
		{
			tileIndex++; continue;
		}

		// 移動先のマスに駒があるか確認
		auto ptrBoard = dynamic_cast<Board*>(_objManager->Get("board"));
		auto ptrPiece = ptrBoard->GetPiece(destIndex);

		// 移動先に自分の駒がある場合は動かせない
		if (ptrPiece->GetPlayerType() == _kPlayerType)
		{
			tileIndex++; continue;
		}

		// 移動先に相手の駒がある場合は取ることができる
		ptrBoard->GetSquare(destIndex)->SetSquareState("Placeable");
		moveCnt++;
		tileIndex++;
	}

	// 移動可能なマスの数を返す
	return moveCnt;
}

bool Piece::IsMove(int index)
{
	// 駒の位置を調べる
	int row = index % BOARD_SIZE;
	int col = index / BOARD_SIZE;

	// 移動範囲の確認
	int moveCnt		= CheckCntMovable(row, col);

	// 移動可能なマスがある場合はtrueを返す
	if (moveCnt > 0)	return true;
	else				return false;
}

bool Piece::Move(int index)
{
	// 移動可能か確認
	if (!IsMove(index)) return false;

	// 移動先のマスを取得する
	auto ptrBoard = dynamic_cast<Board*>(_objManager->Get("board"));
	auto ptrPiece = ptrBoard->GetPiece(index);

	if (ptrPiece)
	{
		int tmp = ptrPiece->GetDan();
		ptrPiece->SetDan(_dan);
		_dan = tmp;

		tmp = ptrPiece->GetSuji();
		ptrPiece->SetSuji(_suji);
		_suji = tmp;
	}
	else
	{
		ptrBoard->SetPiece(index, ptrPiece);
		ptrBoard->SetPiece(_tile, nullptr);
	}

	// 駒の位置情報を更新
	


	return true;
}

// タイルの中央に駒をセットする 
void Piece::PutPieceCentralTile()
{
	// 駒がいる場所を取得する
	auto owner = this->GetOwnerType();

	VECTOR pos = { 0, 0, 0 };

	// 駒と同じ位置にあるタイルを取得する
	if (owner == OWNER_TYPE::Board)
	{
		auto ptrBoard = dynamic_cast<Board*>(_objManager->Get("board"));
		auto ptrSquare = ptrBoard->GetSquare(this->_suji * BOARD_SIZE + this->_dan);
		pos = ptrSquare->GetCenterPos();
	}
	else if(owner == OWNER_TYPE::PieceStand)
	{
		std::string strPieceStand = "PieceStand";
		strPieceStand += _kPlayerType == PLAYER_TYPE::Player1 ? "1" : "2";
		auto ptrPieceStand = dynamic_cast<PieceStand*>(_objManager->Get(strPieceStand.c_str()));

		auto ptrSquare = ptrPieceStand->GetSquare(this->_suji * PIECESTAND_W + this->_dan);
		pos = ptrSquare->GetCenterPos();
	}

	// 駒の位置を少し上にずらす
	// マスの座標をそのままをセットすると、駒が少しだけ埋まってしまうため
	pos.y += 0.5f;

	// タイルの中央に駒の位置をセットする
	this->SetPos(pos);
}

void Piece::UpdateDirectionForPlayer(PLAYER_TYPE playerType)
{
	if (_kOwnerType == OWNER_TYPE::Board) 
	{
		if (playerType == PLAYER_TYPE::Player1) { _rot = VGet(0, 0, 0); }
		if (playerType == PLAYER_TYPE::Player2) { _rot = VGet(0, DEG2RAD(180), 0); }
	}
	else if (_kOwnerType == OWNER_TYPE::PieceStand)
	{
		_rot = VGet(0, 0, 0);
	}
}

