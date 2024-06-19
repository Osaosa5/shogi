
#include "Koma.h"

#include "appframe.h"
#include "Object.h"
#include "Board.h"
#include "Square.h"

Koma::Koma(ObjectManager* objManajer, int dan, int suji, PLAYER_TYPE kPlayer)
{
	_objManager = objManajer;
	_oldPos = VGet(0, 0, 0);
	_bSetPos = false;
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
	SetKomaCentralTile();

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

// TODO:BoardじゃなくてSquareの方がいいかもしれない
bool Koma::GetBoard()
{
	// Boardクラスのポインタを取得
	Object* obj = _objManager->Get("board");
	if (!obj) return false;
	_board = dynamic_cast<Board*>(obj);
	return true;
}

Square* Koma::GetSquarePutKoma()
{
	// 駒の位置を文字列に直し、同じ位置にある"square"と合わせる
	std::string strSquare = "square" + std::to_string(_suji * DAN_MAX + _dan);

	// 駒と同じ位置にあるタイルを取得する
	Object* obj = _objManager->Get(strSquare.c_str());
	if (obj) return dynamic_cast<Square*>(obj);
	else return nullptr;
}

// タイルの中央に駒をセットする 
void Koma::SetKomaCentralTile()
{
	if(_bSetPos) return; 
	Square* square = GetSquarePutKoma();

	// タイルの中央に駒の位置をセットする
	this->SetPos(square->GetCenter());

	// 駒の位置がセットされたことを記録する
	_bSetPos = true;
}

void Koma::SetKomaToSquare()
{
	Square* square = GetSquarePutKoma();

	// 設置してある駒が自分自身の場合は何もしない
	if(square->GetKoma() == this) return;

	// 駒をタイルにセットする
	square->SetKoma(this);
}

