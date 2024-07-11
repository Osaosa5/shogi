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

	// データの読み込み・追加
	void LoadData();
	bool ObjectAdd();

	// ゲッター、セッター
	std::string GetCurrentPlayer()const { return _currentPlayer; }
	void SetCurrentPlayer(std::string strPlayer) { _currentPlayer = strPlayer; }
	void SetWinPlayer(std::string strPlayer) { _strWinPlayer = strPlayer; }

	bool IsWin()const { return _isWin; }
	void SetWin(bool isWin) { _isWin = isWin; }

private:
	// オブジェクト管理
	class ObjectManager* _objectManager;
	std::vector<int> _mapChip;

	// プレイヤー
	std::string _currentPlayer;
	std::string _strWinPlayer;

	// フラグ
	bool _isWin;
}; 
