#pragma once

#include "Object.h"

class ShogiBan : public Object
{
public:
	ShogiBan();
	~ShogiBan();
	static ShogiBan *lpInstance;
	static ShogiBan* GetInstance() { return (ShogiBan*)lpInstance; }

	bool Terminate() override;
	bool Process() override;
	bool Render() override;

	int GetModelHandle() const { return _handle; }
};

