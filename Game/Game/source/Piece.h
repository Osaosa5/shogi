#pragma once

#include "Shogi.h"

#include "ObjectManager.h"
#include "Square.h"

class Piece : public Shogi
{
public:
	Piece(ObjectManager* objManajer, int dan, int suji, std::string strPlayer);
	virtual ~Piece();

	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

public:
	/**
	* @enum 	OWNER_TYPE
	* ������L���A�Ǘ����Ă���I�u�W�F�N�g�̎��
	*/
	enum class OWNER_TYPE 
	{
		//! ��͔Տ�ɂ���
		Board,
		//! ��͋��̏�ɂ���
		PieceStand
	};

	/**
	* @enum 	PIECE_STATE
	* ��̏��
	*/
	enum class PIECE_STATE
	{
		//! ��͉�������Ă��Ȃ�
		None,
		//! ��I������Ă���
		Select,
		//! ��ړ����Ă���
		Move
	};

public:
	/**
	* @brief		None���̏���
	* @return		�����������������ǂ���
	*/
	bool NoneProcess();

	/**
	* @brief		Select���̏���
	* @return		�����������������ǂ���
	*/
	bool SelectProcess();

	/**
	* @brief		Move���̏���
	* @return		�����������������ǂ���
	*/
	bool MoveProcess();


	/**
	* @brief		�R�}�̈ړ��悪�ǂ������ׂ�
	* @param[in]	index		�R�}�̃C���f�b�N�X
	* @param[in]	row			�s
	* @param[in]	col			��
	* @return		�ړ��悪�ǂ��� ���m�ɂ͔z��̃C���f�b�N�X
	*/
	int		CheckDest(int index, int row, int col);

	/**
	* @brief		�R�}���ړ��\�ȃ}�X�̐��𒲂ׂ�
	* @param[in]	row			�s
	* @param[in]	col			��
	* @return		�ړ��\�ȃ}�X�̐�
	*/
	int		CheckCntMovable(int row, int col);

	/**
	* @brief		�R�}���ړ��\���𒲂ׂ�
	* @param[in]	index		�R�}�̃C���f�b�N�X
	* @return		�ړ��\���ǂ���
	*				true: �ړ��� false: �ړ��s��
	*/
	bool	IsMove(int index);

	/**
	* @brief		�R�}���ړ�����
	* @param[in]	index		�R�}�̃C���f�b�N�X
	* @return		�ړ��ł������ǂ���
	* 				true: �ړ��� false: �ړ��s��
	*/
	bool Move(int index);

	/**
	* @brief		�R�}���}�X�̒����ɒu��
	*/
	void PutPieceCentralTile();

	/**
	* @brief		�v���C���[�̕������X�V����
	* @param[in]	playerType		�v���C���[�̎��
	* @detail		�v���C���[�̎�ނɂ���āA������������قȂ�
	*/
	void UpdateDirectionForPlayer(PLAYER_TYPE playerType);

	// �Q�b�^�[
	/**
	* @brief		3D���W�̍X�V�t���O���擾����
	* @return		3D���W�̍X�V�t���O
	* @detail		true�̏ꍇ�A��}�X�̒����ɒu�����
	*/
	bool GetUpdate3DPos() const	{ return _bUpdate3DPos; }

	/**
	* @brief		��̏��L�҂��擾����
	* @return		���L��
	*				Board:��͔Տ�ɂ���
	*				PieceStand:��͋��̏�ɂ���
	*/
	OWNER_TYPE			GetOwnerType() const	{ return _kOwnerType; }

	/**
	* @brief		��̈ړ��͈͂��擾����
	* @return		��̈ړ��͈�(vector)
	* @detail		�ړ��͈͂͋�̎�ނɂ���ĈقȂ�
	*				17*17�̔z��ŕ\�������
	*/
	std::vector<int>	GetMoveRange() const	{ return _vMoveRange; }

	/**
	* @brief		��̏�Ԃ��擾����
	* @return		��̏��
	* 				None: ��͉�������Ă��Ȃ�
	* 				Select: ��I������Ă���
	* 				Move: ��ړ����Ă���
	*/
	PIECE_STATE			GetPieceState() const { return _kPieceState; }

	// �Z�b�^�[
	/**
	* @brief		3D���W�̍X�V�t���O��ݒ肷��
	* @param[in]	bUpdate3DPos	3D���W�̍X�V�t���O
	* @detail		true�̏ꍇ�A��}�X�̒����ɒu�����
	*/
	void SetUpdate3DPos(bool bUpdate3DPos)	{ _bUpdate3DPos = bUpdate3DPos; }

	/**
	* @brief		��̏��L�҂�ݒ肷��
	* @param[in]	ownerType		���L��
	* 				Board:��͔Տ�ɂ���
	* 				PieceStand:��͋��̏�ɂ���
	*/
	void SetOwnerType(OWNER_TYPE ownerType)	{ _kOwnerType = ownerType; }

	/**
	* @beief		��̏�Ԃ�ݒ肷��
	* @param[in]	pieceState		��̏��
	* 				None: ��͉�������Ă��Ȃ�
	* 				Select: ��I������Ă���
	* 				Move: ��ړ����Ă���
	*/
	void SetPieceState(PIECE_STATE pieceState) { _kPieceState = pieceState; }

protected:
	bool				_bUpdate3DPos;	//! 3D���W�̍X�V�t���O
	OWNER_TYPE			_kOwnerType;	//! ��̏��L��
	std::vector<int>	_vMoveRange;	//! ��̈ړ��͈�
	PIECE_STATE			_kPieceState;	//! ��̏��

private:
	ObjectManager* _objManager;	//! �I�u�W�F�N�g�}�l�[�W��	�A�O���Q�[�V�����̊֌W�ɂ���
};

