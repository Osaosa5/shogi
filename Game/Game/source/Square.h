#pragma once

#include "Shogi.h"
#include "ObjectManager.h"
#include "Koma.h"

class Square : public Shogi
{
public:
	Square(ObjectManager* objManeger, VECTOR pos, std::pair<float, float> size, int mapChip, std::string player, int dan, int suji);
	~Square();

	bool Terminate() override;
	bool Process() override;
	bool Render() override;

	KOMA_TYPE GetKomaAt();

	VECTOR GetCenter() const { return _center; }
	int GetTileNum() const { return _tile; }
	KOMA_TYPE GetKomaType() const { return _komaType; }
	AREA_TYPE GetAreaType() const { return _areaType; }
	class Koma *GetKoma() const { return _koma; }
	void SetKoma(Koma* koma) { _koma = koma; }

private:
	ObjectManager* _objManager;
	std::pair<float, float> _size;
	VECTOR _center;
	Koma* _koma;
};

