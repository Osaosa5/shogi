#include "Vector2.h"
#include <math.h>
// 加算
Vector2 Vector2::operator+=(const Vector2& right)
{
	Vector2 result = Vector2();
	result._x = _x + right._x;
	result._y = _y + right._y;
	return result;
}

// 減算
Vector2 Vector2::operator-=(const Vector2& right)
{
	Vector2 result = Vector2();
	result._x = _x - right._x;
	result._y = _y - right._y;
	return result;
}

// 乗算 ベクトル × ベクトル
Vector2 Vector2::operator*=(const Vector2& right)
{
	Vector2 result = Vector2();
	result._x = _x * right._x;
	result._y = _y * right._y;
	return result;
}

// 乗算 ベクトル × 実数
Vector2 Vector2::operator*=(const double& right)
{
	Vector2 result = Vector2();
	result._x = _x * right;
	result._y = _y * right;
	return result;
}

// 除算 ベクトル ÷ ベクトル
Vector2 Vector2::operator/=(const Vector2& right)
{
	Vector2 result = Vector2();
	result._x = _x / right._x;
	result._y = _y / right._y;
	return result;
}

// 除算 ベクトル ÷ 実数
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