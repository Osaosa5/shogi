#include "appframe.h"

class ApplicationGlobal
{
public:
	ApplicationGlobal();
	virtual ~ApplicationGlobal();

	bool Init();

};

// 他のソースでgGlobalを使えるように
extern ApplicationGlobal		gGlobal;
