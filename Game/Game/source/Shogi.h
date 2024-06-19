#pragma once

#include "Object.h"

class Shogi : public Object
{
public:
	Shogi();
	~Shogi();

	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	int GetDan() { return _dan; }
	void SetDan(int dan) { _dan = dan; }

	int GetSuji() { return _suji; }
	void SetSuji(int suji) { _suji = suji; }

	int GetTile() { return _tile; }
	void SetTile(int tile) { _tile = tile; }

	enum AREA_TYPE	// �G���A�̎��
	{
		kNone,		// �Ȃ�
		kNeutral,	// ����
		kPlayer1Area,	// Player1
		kPlayer2Area		// Player2
	};

	enum KOMA_TYPE	// ��̎��
	{
		kNoneKoma,
		kFuhyo,		// ����
		kKyosha,	// ����
		kKeima,		// �j�n
		kGinsho,	// �⏫
		kKinsho,	// ����
		kKakugyo,	// �p�s
		kRyume,		// ���n
		kHisha,		// ���
		kRyuo,		// ����
		kOsho,		// ����
	};

	enum PLAYER_TYPE	// �v���C���[�̎��
	{
		kNonePlayer,		// �Ȃ�
		kPlayer1,	// Player1
		kPlayer2	// Player2
	};

	const int SUJI_MAX = 9;	// �c�̗�̍ő吔
	const int DAN_MAX = 9;	// ���̍s�̍ő吔

protected:
	int _suji;	// �c�̗�
	int _dan;	// ���̍s
	int _tile;	// �z��̗v�f�ԍ�
	AREA_TYPE _areaType;	// �G���A�̎��
	KOMA_TYPE _komaType;	// ��̎��
	PLAYER_TYPE _playerType;	// �v���C���[�̎��
};

