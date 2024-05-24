#pragma once

#include "Object.h"

#include "appframe.h"

class Camera : public Object
{
public:
	Camera();
	~Camera();

	bool Initialize() override;
	bool Terminate() override;
	bool Process() override;
	bool Render() override;

private:
	VECTOR	_direction;
	float	_clipNear, _clipFar;
};

