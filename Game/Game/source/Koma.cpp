
#include "Koma.h"

#include "appframe.h"
#include "Object.h"
#include "Square.h"

Koma::Koma(ObjectManager* objManajer, int dan, int suji, PLAYER_TYPE kPlayer)
{
	_objManager = objManajer;
	_oldPos = VGet(0, 0, 0);
	_bIsRegisterKomaToSquare = true;
	_bUpdateBoardPos = true;
	_bUpdate3DPos = true;
	// ��̈ʒu���
	_dan = dan; _suji = suji;
	_tile = _suji * DAN_MAX + _dan;
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

	if(_bIsRegisterKomaToSquare) RegisterKomaToSquare();

	if (_bUpdate3DPos) SetKomaCentralTile();

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
	auto shogiBan = _objManager->Get("shogiban");
	auto shogiBanHandle = shogiBan->GetHandle();
	hitPoly = MV1CollCheck_Line(shogiBanHandle, 2,
		VAdd(_pos, VGet(0, colSubY, 0)),
		VAdd(_pos, VGet(0, -999, 0)));
	if (hitPoly.HitFlag)
	{
		// �����ꍇ
		_pos.y = hitPoly.HitPosition.y + 0.3f;
	}
	else
	{
		// ��Ȃ��ꍇ
		_pos = _oldPos;
	}

}

// ����^�C���ɓo�^����
void Koma::RegisterKomaToSquare()
{
	GetSquarePutKoma(_dan, _suji)->SetKoma(this);
	_bIsRegisterKomaToSquare = false;
}

Square* Koma::GetSquarePutKoma(int dan, int suji)
{
	// ��̈ʒu�𕶎���ɒ����A�����ʒu�ɂ���"square"�ƍ��킹��
	std::string strSquare = "square" + std::to_string(suji * DAN_MAX + dan);

	// ��Ɠ����ʒu�ɂ���^�C�����擾����
	Object* obj = _objManager->Get(strSquare.c_str());
	if (obj) return dynamic_cast<Square*>(obj);
	else return nullptr;
}

// �^�C���̒����ɋ���Z�b�g���� 
void Koma::SetKomaCentralTile()
{
	Square* square = GetSquarePutKoma(_dan, _suji);

	// �^�C���̒����ɋ�̈ʒu���Z�b�g����
	this->SetPos(square->GetCenter());

	// ��̈ʒu���Z�b�g���ꂽ���Ƃ��L�^����
	_bUpdate3DPos = false;
}

