#pragma once

class Vector2
{
public:
	Vector2() { _x = 0; _y = 0; }
	Vector2(double x, double y) { _x = x; _y = y; }
	~Vector2() = default;

	// �l�����Z
	Vector2 operator+=(const Vector2& right);	// ���Z
	Vector2 operator-=(const Vector2& right);	// ���Z
	Vector2 operator*=(const Vector2& right);	// ��Z�@�x�N�g�� �~ �x�N�g��
	Vector2 operator*=(const double& right);		// ��Z�@�x�N�g�� �~ �萔
	Vector2 operator/=(const Vector2& right);	// ���Z�@�x�N�g�� �� �x�N�g��
	Vector2 operator/=(const double& right);		// ���Z�@�x�N�g�� �� �萔

public:
	double _x, _y;
};

const Vector2 operator+(const Vector2& left, const Vector2& right);		// ���Z	
const Vector2 operator-(const Vector2& left, const Vector2& right);		// ���Z	
const Vector2 operator*(const Vector2& left, const Vector2& right);		// ��Z�@
