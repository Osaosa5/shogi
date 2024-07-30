#pragma once

#include "Shogi.h"
#include "ObjectManager.h"
#include "Piece.h"
#include "ModeGame.h"

class Player : public Shogi
{
	using SelectSquarePos = std::pair<int, int>;
public:
	Player(ObjectManager* objManeger, std::string player, ModeGame* game);
	~Player();

	bool Initialize()	override;
	bool Terminate()	override;
	bool Process()		override;
	bool Render()		override;

	void SelectSquare(int trg);	

	// �����Ղ̋�𓮂�������
	void SelectBoardPiece(int index);
	void MoveBoardPiece(int index);
	Piece* TakePiece(Piece* ptrPiece);

	// ���̋�𓮂�������
	void SelectStandPiece(int index);
	void MoveStandPiece(int index);

	void ChangeSelectBoardToStand();
	void ChangeSelectStandToBoard();

	void SelectBoardSquare(int index);
	void SelectPieceStandSquare(int index);

	enum class PLAYER_STATE
	{
		SelectBoardSquare,
		SelectPieceStandSquare
	};

	PLAYER_STATE	GetState()const					{ return _state; }
	void			SetState(PLAYER_STATE state)	{ _state = state; }

private:
	// �Q�Ƃ���N���X�̃|�C���^
	ObjectManager*	_objManager;
	ModeGame*		_game;

	// �I�����Ă����̃C���f�b�N�X
	int				_selectedPieceIndex;

	// �I�����Ă���}�X�̍��W
	// first : �i(int), second : ��(int)
	SelectSquarePos	_selectSquareBoard;
	SelectSquarePos	_selectSquareStand;

	// �v���C���[�̏��
	PLAYER_STATE	_state;
	bool			_isSelectPieceOfPieceStand;
};

