#pragma once

#include "Shogi.h"
#include "ObjectManager.h"
#include "Piece.h"

class Square : public Shogi
{
public:
	Square(VECTOR pos, std::string player, int dan, int suji);
	~Square();

	bool Terminate() override;
	bool Process() override;
	bool Render() override;

	std::pair<float, float> GetSize() const { return _size; }

	VECTOR GetCenterPos() const { return _center; }

	bool GetSelect() const { return _bSelect; }
	void SetSelect(bool bSelect) { _bSelect = bSelect; }

	AREA_TYPE GetAreaType() const { return _kAreaType; }

private:
	std::pair<float, float> _size;
	VECTOR _center;
	bool _bSelect;
};

