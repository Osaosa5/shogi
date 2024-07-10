#pragma once

#include "appframe.h"

// ���[�h
class ModeGame : public ModeBase
{
	typedef ModeBase base;
public:
	bool Initialize()override;
	bool Terminate()override;
	bool Process()override;
	bool Render()override;

	// �f�[�^�̓ǂݍ��݁E�ǉ�
	void LoadData();
	bool ObjectAdd();

	// �Q�b�^�[�A�Z�b�^�[
	std::string GetCurrentPlayer()const { return _currentPlayer; }
	void SetCurrentPlayer(std::string strPlayer) { _currentPlayer = strPlayer; }
	void SetWinPlayer(std::string strPlayer) { _strWinPlayer = strPlayer; }

	bool IsWin()const { return _isWin; }
	void SetWin(bool isWin) { _isWin = isWin; }

private:
	// �I�u�W�F�N�g�Ǘ�
	class ObjectManager* _objectManager;
	std::vector<int> _mapChip;

	// �v���C���[
	std::string _currentPlayer;
	std::string _strWinPlayer;

	// �t���O
	bool _isWin;
}; 
