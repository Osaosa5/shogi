#pragma once

#include "Object.h"

class ShogiBan : public Object
{
public:
	ShogiBan();
	~ShogiBan();

	bool Terminate() override;
	bool Process() override;
	bool Render() override;
};

