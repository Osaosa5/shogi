#include "Vector2.h"
#include <math.h>
// ���Z
Vector2 Vector2::operator+=(const Vector2& right)
{
	Vector2 result = Vector2();
	result._x = _x + right._x;
	result._y = _y + right._y;
	return result;
}

// ���Z
Vector2 Vector2::operator-=(const Vector2& right)
{
	Vector2 result = Vector2();
	result._x = _x - right._x;
	result._y = _y - right._y;
	return result;
}

// ��Z �x�N�g�� �~ �x�N�g��
Vector2 Vector2::operator*=(const Vector2& right)
{
	Vector2 result = Vector2();
	result._x = _x * right._x;
	result._y = _y * right._y;
	return result;
}

// ��Z �x�N�g�� �~ ����
Vector2 Vector2::operator*=(const double& right)
{
	Vector2 result = Vector2();
	result._x = _x * right;
	result._y = _y * right;
	return result;
}

// ���Z �x�N�g�� �� �x�N�g��
Vector2 Vector2::operator/=(const Vector2& right)
{
	Vector2 result = Vector2();
	result._x = _x / right._x;
	result._y = _y / right._y;
	return result;
}

// ���Z �x�N�g�� �� ����
Vector2 Vector2::operator/=(const double& right)
{
	Vector2 result = Vector2();
	result._x = _x / right;
	result._y = _y / right;
	return result;
}

const Vector2 operator+(const Vector2& left, const Vector2& right) { return Vector2(left) += right; }
const Vector2 operator-(const Vector2& left, const Vector2& right) { return Vector2(left) -= right; }
const Vector2 operator*(const Vector2& left, const Vector2& right) { return Vector2(left) *= right; }