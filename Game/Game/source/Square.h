#pragma once

#include "Shogi.h"
#include "ObjectManager.h"
#include "Piece.h"

class Square : public Shogi
{
public:
	Square(ObjectManager* objManeger, VECTOR pos, std::pair<float, float> size, int mapChip, std::string player, int dan, int suji);
	~Square();

	bool Terminate() override;
	bool Process() override;
	bool Render() override;

	std::pair<float, float> GetSize() const { return _size; }

	VECTOR GetCenter() const { return _center; }

	class Piece* GetKoma() const { return _piece; }
	void SetKoma(Piece* piece) { _piece = piece; }

	bool GetSelect() const { return _bSelect; }
	void SetSelect(bool bSelect) { _bSelect = bSelect; }

	int GetTileNum() const { return _tile; }
	PIECE_TYPE GetKomaType() const { return _pieceType; }
	AREA_TYPE GetAreaType() const { return _areaType; }

private:
	ObjectManager* _objManager;
	std::pair<float, float> _size;
	VECTOR _center;
	Piece* _piece;
	bool _bSelect;
};

