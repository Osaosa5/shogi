#pragma once

#include "Object.h"
#include "ObjectManager.h"
#include "ShogiBan.h"

class Koma : public Object
{
public:
	Koma(ObjectManager* objManajer);
	virtual ~Koma();

	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	virtual bool Move();

private:
	ObjectManager* _objManajer;
};

