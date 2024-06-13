#pragma once

#include "Shogi.h"

class Square : public Shogi
{
public:
	Square(VECTOR pos, std::pair<float, float> size, int mapChip, std::string player);
	~Square();

	bool Terminate() override;
	bool Process() override;
	bool Render() override;

	int GetMapChip() { return _mapChip; }
	KOMA_TYPE GetKomaType() { return _komaType; }
	AREA_TYPE GetAreaType() { return _areaType; }

private:
	std::pair<float, float> _size;
	VECTOR _center;
};

