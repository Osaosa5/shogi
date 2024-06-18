#pragma once

#include "Shogi.h"

class Square : public Shogi
{
public:
	Square(VECTOR pos, std::pair<float, float> size, int mapChip, std::string player, int dan, int suji);
	~Square();

	bool Terminate() override;
	bool Process() override;
	bool Render() override;

	VECTOR GetCenter() const { return _center; }

	int GetTileNum() const { return _tile; }
	KOMA_TYPE GetKomaType() const { return _komaType; }
	AREA_TYPE GetAreaType() const { return _areaType; }

private:
	std::pair<float, float> _size;
	VECTOR _center;
};

