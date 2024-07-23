#pragma once

#include "Object.h"

constexpr int	BOARD_SIZE		= 9;	
constexpr int	BOARD_TILE		= 81;

constexpr float SQUARE_WIDTH	= 3.52f;
constexpr float SQUARE_HEIGHT	= 3.86f;


class Shogi : public Object
{
public:
	Shogi();
	~Shogi();

	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	int GetDan() const { return _dan; }
	void SetDan(int dan) { _dan = dan; }

	int GetSuji() const { return _suji; }
	void SetSuji(int suji) { _suji = suji; }

	int GetTile() const { return _tile; }
	void SetTile(int tile) { _tile = tile; }

	enum AREA_TYPE	// �G���A�̎��
	{
		kNone,		// �Ȃ�
		kNeutral,	// ����
		kPlayer1Area,	// Player1
		kPlayer2Area		// Player2
	};

	enum PIECE_TYPE	// ��̎��
	{
		kNonePiece,
		kPawn,		// ����
		kLance,		// ����
		kKnight,	// �j�n
		kSilver,	// �⏫
		kGold,		// ����
		kBishop,	// �p�s
		kRyume,		// ���n
		kRook,		// ���
		kRyuo,		// ����
		kKing,		// ����
	};

	enum PLAYER_TYPE	// �v���C���[�̎��
	{
		kNonePlayer,		// �Ȃ�
		kPlayer1,	// Player1
		kPlayer2	// Player2
	};

	AREA_TYPE GetAreaType() const { return _areaType; }
	void SetAreaType(AREA_TYPE areaType) { _areaType = areaType; }

	PIECE_TYPE GetPieceType() const { return _pieceType; }
	void SetPieceType(PIECE_TYPE pieceType) { _pieceType = pieceType; }

	PLAYER_TYPE GetPlayerType() const { return _playerType; }
	void SetPlayerType(PLAYER_TYPE playerType) { _playerType = playerType; }

protected:
	int _suji;	// �c�̗�
	int _dan;	// ���̍s
	int _tile;	// �z��̗v�f�ԍ�
	AREA_TYPE _areaType;	// �G���A�̎��
	PIECE_TYPE _pieceType;	// ��̎��
	PLAYER_TYPE _playerType;	// �v���C���[�̎��
};

