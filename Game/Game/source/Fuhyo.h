#pragma once

#include "Koma.h"

class Fuhyo : public Koma
{
public:
	Fuhyo(ObjectManager* objManajer, int dan, int suji, PLAYER_TYPE kPlayer);
	~Fuhyo();

	bool Terminate()override;
	bool Process()override;
	bool Render()override;

	bool Move()override;

	//3d��ԂɑΉ��������W
	// ���ڂɑΉ��������W
	//�I���W�i���^�C�v�g���̂��
};

