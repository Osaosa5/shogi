#pragma once

#include "appframe.h"

// モード
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
	// オブジェクト管理
	class ObjectManager* _objectManager;
	std::vector<int> _mapChip;

	// プレイヤー
	std::string _strWinPlayer;

	// フラグ
	bool _isWin;
}; 
