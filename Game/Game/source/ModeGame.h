
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

	bool ObjectAdd();

private:
	// �I�u�W�F�N�g�Ǘ�
	class ObjectManager* _objectManager;

}; 
