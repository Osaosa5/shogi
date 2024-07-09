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

	void LoadData();
	bool ObjectAdd();

	bool IsWin()const { return _isWin; }
	void SetWin(bool isWin) { _isWin = isWin; }

	void SetWinPlayer(std::string strPlayer){ _strWinPlayer = strPlayer; }

private:
	// �I�u�W�F�N�g�Ǘ�
	class ObjectManager* _objectManager;
	std::vector<int> _mapChip;

	// �v���C���[
	std::string _strWinPlayer;

	// �t���O
	bool _isWin;
}; 
