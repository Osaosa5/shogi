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
	void SetBoardTile(int dan, int suji, int tile) { _vBoardTiles[suji * DAN_MAX + dan] = tile; }
	int GetBoardTile(int tile){ return _vBoardTiles[tile]; }
	int GetBoardTile(int dan, int suji) { return _vBoardTiles[suji * DAN_MAX + dan]; }

private:
	std::vector<int> _vBoardTiles;

};

