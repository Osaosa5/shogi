#pragma once

#include "Object.h"

constexpr int	BOARD_SIZE		= 9;	
constexpr int	BOARD_TILE		= 81;

constexpr int	PIECESTAND_W	= 3;
constexpr int	PIECESTAND_H	= 3;
constexpr int	PIECESTAND_NUM	= 7;

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

	int		GetDan() const		{ return _dan; }
	void	SetDan(int dan)		{ _dan = dan; }

	int		GetSuji() const		{ return _suji; }
	void	SetSuji(int suji)	{ _suji = suji; }

	int		GetTile() const		{ return _tile; }
	void	SetTile(int tile)	{ _tile = tile; }

	enum class AREA_TYPE	// �G���A�̎��
	{
		None,			// �Ȃ�
		Neutral,		// ����
		Player1Area,	// Player1
		Player2Area	// Player2
	};

	enum class PIECE_TYPE	// ��̎��
	{
		None,
		Pawn,		// ����
		Lance,		// ����
		Knight,		// �j�n
		Silver,		// �⏫
		Gold,		// ����
		Bishop,		// �p�s
		Ryume,		// ���n
		Rook,		// ���
		Ryuo,		// ����
		King,		// ����
	};

	enum class PLAYER_TYPE	// �v���C���[�̎��
	{
		None,	// �Ȃ�
		Player1,		// Player1
		Player2		// Player2
	};

	AREA_TYPE	GetAreaType() const						{ return _kAreaType; }
	void		SetAreaType(AREA_TYPE areaType)			{ _kAreaType = areaType; }

	PIECE_TYPE	GetPieceType() const					{ return _kPieceType; }
	void		SetPieceType(PIECE_TYPE pieceType)		{ _kPieceType = pieceType; }

	PLAYER_TYPE GetPlayerType() const					{ return _kPlayerType; }
	void		SetPlayerType(PLAYER_TYPE playerType)	{ _kPlayerType = playerType; }

protected:
	int _suji;	// �c�̗�
	int _dan;	// ���̍s
	int _tile;	// �z��̗v�f�ԍ�

	AREA_TYPE	_kAreaType;		// �G���A�̎��
	PIECE_TYPE	_kPieceType;	// ��̎��
	PLAYER_TYPE _kPlayerType;	// �v���C���[�̎��
};

