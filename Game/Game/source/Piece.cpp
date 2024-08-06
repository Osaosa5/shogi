
#include "Piece.h"

#include "appframe.h"
#include "Board.h"
#include "PieceStand.h"

Piece::Piece(ObjectManager* objManajer, int dan, int suji, std::string strPlayer)
{
	_objManager = objManajer;
	_oldPos = VGet(0, 0, 0);
	_bUpdate3DPos = true;
	_kOwnerType = OWNER_TYPE::Board;

	// 駒の位置情報
	_dan = dan; _suji = suji;
	_tile = _suji * BOARD_SIZE + _dan;

	// プレイヤー情報
	if (strPlayer == "player1") _kPlayerType = PLAYER_TYPE::Player1;
	if (strPlayer == "player2") _kPlayerType = PLAYER_TYPE::Player2;
	UpdateDirectionForPlayer(_kPlayerType);
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

	//if (_bUpdate3DPos) 
	SetPieceCentralTile();

	UpdateDirectionForPlayer(_kPlayerType);

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
		//_pos = _oldPos;
	}

}

// タイルの中央に駒をセットする 
void Piece::SetPieceCentralTile()
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
	// タイルの中央に駒の位置をセットする
	this->SetPos(pos);

	// 駒の位置がセットされたことを記録する
	_bUpdate3DPos = false;
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

