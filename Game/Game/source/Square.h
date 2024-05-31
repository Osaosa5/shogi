#pragma once

#include "Shogi.h"

class Square : public Shogi
{
public:
	Square();
	~Square();

	bool Terminate() override;
	bool Process() override;
	bool Render() override;

	
};

