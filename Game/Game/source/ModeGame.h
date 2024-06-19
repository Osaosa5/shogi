
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

private:
	// オブジェクト管理
	class ObjectManager* _objectManager;
	std::vector<int> _mapChip;
}; 
