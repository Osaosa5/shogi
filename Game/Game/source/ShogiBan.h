#pragma once

#include "Object.h"

class ShogiBan : public Object
{
public:
	ShogiBan();
	~ShogiBan();

	bool Initialize() override;
	bool Terminate() override;
	bool Process() override;
	bool Render() override;
};

