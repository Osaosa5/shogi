#include "appframe.h"

class ApplicationGlobal
{
public:
	ApplicationGlobal();
	virtual ~ApplicationGlobal();

	bool Init();

};

// ���̃\�[�X��gGlobal���g����悤��
extern ApplicationGlobal		gGlobal;
