
#include "Piece.h"

#include "appframe.h"
#include "Board.h"

Piece::Piece(ObjectManager* objManajer, int dan, int suji, PLAYER_TYPE kPlayer)
{
	_objManager = objManajer;
	_oldPos = VGet(0, 0, 0);
	_bIsRegisterPieceToSquare = true;
	_bUpdateBoardPos = true;
	_bUpdate3DPos = true;
	// 駒の位置情報
	_dan = dan; _suji = suji;
	_tile = _suji * BOARD_SIZE + _dan;
	// プレイヤー情報
	_playerType = kPlayer;
	if (_playerType == kPlayer1) { _rot = VGet(0, 0, 0); }
	else if (_playerType == kPlayer2) { _rot = VGet(0, DEG2RAD(180), 0); }
}

Piece::~Piece()
{
}

bool Piece::Terminate()
{
	return true;
}

bool Piece::Process()
{
	_oldPos = _pos;

	if (_bUpdate3DPos) SetPieceCentralTile();

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

bool Piece::Move()
{
	return true;
}

void Piece::HitTest()
{
	float colSubY = 40.0f;
	// 駒の当たり判定
	MV1_COLL_RESULT_POLY hitPoly;
	auto shogiBan = _objManager->Get("shogiban");
	auto shogiBanHandle = shogiBan->GetHandle();
	hitPoly = MV1CollCheck_Line(shogiBanHandle, 2,
		VAdd(_pos, VGet(0, colSubY, 0)),
		VAdd(_pos, VGet(0, -999, 0)));
	if (hitPoly.HitFlag)
	{
		// 駒がある場合
		_pos.y = hitPoly.HitPosition.y + 0.3f;
	}
	else
	{
		// 駒がない場合
		_pos = _oldPos;
	}

}

// タイルの中央に駒をセットする 
void Piece::SetPieceCentralTile()
{
	// 駒と同じ位置にあるタイルを取得する
	auto board = dynamic_cast<Board*>(_objManager->Get("board"));
	auto square = board->GetSquare(_tile);

	// タイルの中央に駒の位置をセットする
	this->SetPos(square->GetCenter());

	// 駒の位置がセットされたことを記録する
	_bUpdate3DPos = false;
}

