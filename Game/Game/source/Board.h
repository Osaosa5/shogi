#pragma once

#include "Shogi.h"
#include "Square.h"
#include "ObjectManager.h"

class Board : public Shogi
{
public:
	Board(ObjectManager* objManager);
	~Board();

	bool Terminate() override;
	bool Process() override;
	bool Render() override;

	Square* GetSquare(int element) { return _squares[element]; }
	void SetSquare(int element, Square* square) { _squares[element] = square; }

private:
	Square* _squares[BOARD_TILE];
};

