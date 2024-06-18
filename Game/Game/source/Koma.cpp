
#include "Koma.h"

#include "appframe.h"
#include "Object.h"
#include "Board.h"
#include "Square.h"

Koma::Koma(ObjectManager* objManajer, VECTOR pos, int dan, int suji, PLAYER_TYPE kPlayer)
{
	_objManajer = objManajer;
	_oldPos = VGet(0, 0, 0);
	// 位置情報
	_pos = pos;
	// 駒の位置情報
	_dan = dan; _suji = suji;
	// プレイヤー情報
	_playerType = kPlayer;
	if (_playerType == kPlayer1) { _rot = VGet(0, 0, 0); }
	else if (_playerType == kPlayer2) { _rot = VGet(0, DEG2RAD(180), 0); }
}

Koma::~Koma()
{
}

bool Koma::Terminate()
{
	return true;
}

bool Koma::Process()
{
	_oldPos = _pos;

	return true;
}

bool Koma::Render()
{
	// 角度と位置をセットして描画
	MV1SetRotationXYZ(_handle, _rot);
	MV1SetPosition(_handle, _pos);
	MV1DrawModel(_handle);

	return true;
}

bool Koma::Move()
{
	return true;
}

void Koma::HitTest()
{
	float colSubY = 40.0f;
	// 駒の当たり判定
	MV1_COLL_RESULT_POLY hitPoly;
	auto shogiBan = _objManajer->Get("shogiban");
	auto shogiBanHandle = shogiBan->GetHandle();
	hitPoly = MV1CollCheck_Line(shogiBanHandle, 2,
		VAdd(_pos, VGet(0, colSubY, 0)),
		VAdd(_pos, VGet(0, -999, 0)));
	if (hitPoly.HitFlag)
	{
		// 駒がある場合
		_pos.y = hitPoly.HitPosition.y;
	}
	else
	{
		// 駒がない場合
		_pos = _oldPos;
	}

}

// TODO:BoardじゃなくてSquareの方がいいかもしれない
bool Koma::GetBoard()
{
	// Boardクラスのポインタを取得
	Object* obj = _objManajer->Get("board");
	if (!obj) return false;
	_board = dynamic_cast<Board*>(obj);
	return true;
}

// TODO:タイルの中央に駒をセットする 動作を確認すること！
void Koma::SetKomaCentralTile()
{
	// todo:駒の位置を文字列に直し、"square"と合わせる
	std::string strSquare = "square" + std::to_string(_suji * DAN_MAX + _dan);

	// todo:駒と同じ位置にあるタイルを取得する
	Object* obj = _objManajer->Get(strSquare.c_str());
	if (!obj) return;
	Square* square = dynamic_cast<Square*>(obj);

	// todo:タイルの中央に駒の位置をセットする
	this->SetPos(square->GetCenter());
}

