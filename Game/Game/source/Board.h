#pragma once

#include "Shogi.h"

#include "ObjectManager.h"

class Board : public Shogi
{
public:
	Board(ObjectManager* objManeger, nlohmann::json map);
	~Board();

	bool Terminate() override;
	bool Process() override;
	bool Render() override;

	std::vector<int> GetBoardTiles() { return _vBoardTiles; }

private:
	std::vector<int> _vBoardTiles;

};

