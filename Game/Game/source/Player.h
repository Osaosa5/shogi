#pragma once

#include "Shogi.h"
#include "ObjectManager.h"
#include "Square.h"
#include "Koma.h"

class Player : public Shogi
{
public:
	Player(ObjectManager* objManeger, std::string player);
	~Player();

	bool Terminate() override;
	bool Process() override;
	bool Render() override;

	Koma* GetKoma(int dan, int suji);

	void SelectSquare(int trg);

	Square* GetSquare(int dan, int suji);

private:
	ObjectManager* _objManager;
	bool _bSelect;
	std::pair<int, int> _saveSquare;
};

