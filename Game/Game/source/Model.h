#pragma once

#include "Object.h"
#include "appframe.h"

class Model : public Object
{
public:
	Model();
	virtual ~Model();

	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:
	// ��{���
	int		_modelHandle;	// ���f���n���h��
	VECTOR	_pos;			// �ʒu
	VECTOR	_rot;			// ��]
};

