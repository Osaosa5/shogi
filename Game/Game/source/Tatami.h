#pragma once

#include "appframe.h"

#include "Object.h"

class Tatami : public Object
{
public:
	Tatami(VECTOR pos);
	~Tatami();

	bool Terminate() override;
	bool Render() override;
};

