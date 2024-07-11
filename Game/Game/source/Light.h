#pragma once

#include "Object.h"

class Light : public Object
{
public:
	Light();
	~Light();

	bool Terminate() override;
};

