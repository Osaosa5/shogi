
#include "Koma.h"

#include "appframe.h"
#include "Object.h"
#include "Board.h"

Koma::Koma(ObjectManager* objManajer, VECTOR pos, int dan, int suji, PLAYER_TYPE kPlayer)
{
	_objManajer = objManajer;
	_oldPos = VGet(0, 0, 0);
	// �ʒu���
	_pos = pos;
	// ��̈ʒu���
	_dan = dan; _suji = suji;
	// �v���C���[���
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
	// �p�x�ƈʒu���Z�b�g���ĕ`��
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
	// ��̓����蔻��
	MV1_COLL_RESULT_POLY hitPoly;
	auto shogiBan = _objManajer->Get("shogiban");
	auto shogiBanHandle = shogiBan->GetHandle();
	hitPoly = MV1CollCheck_Line(shogiBanHandle, 2,
		VAdd(_pos, VGet(0, colSubY, 0)),
		VAdd(_pos, VGet(0, -999, 0)));
	if (hitPoly.HitFlag)
	{
		// �����ꍇ
		_pos.y = hitPoly.HitPosition.y;
	}
	else
	{
		// ��Ȃ��ꍇ
		_pos = _oldPos;
	}

}

bool Koma::GetBoard()
{
	// Board�N���X�̃|�C���^���擾
	Object* obj = _objManajer->Get("board");
	if (!obj) return false;
	_board = dynamic_cast<Board*>(obj);
	return true;
}

