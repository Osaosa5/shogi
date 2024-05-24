#pragma once

class Vector2
{
public:
	Vector2() { _x = 0; _y = 0; }
	Vector2(double x, double y) { _x = x; _y = y; }
	~Vector2() = default;

	// 四則演算
	Vector2 operator+=(const Vector2& right);	// 加算
	Vector2 operator-=(const Vector2& right);	// 減算
	Vector2 operator*=(const Vector2& right);	// 乗算　ベクトル × ベクトル
	Vector2 operator*=(const double& right);		// 乗算　ベクトル × 定数
	Vector2 operator/=(const Vector2& right);	// 除算　ベクトル ÷ ベクトル
	Vector2 operator/=(const double& right);		// 除算　ベクトル ÷ 定数

public:
	double _x, _y;
};

const Vector2 operator+(const Vector2& left, const Vector2& right);		// 加算	
const Vector2 operator-(const Vector2& left, const Vector2& right);		// 減算	
const Vector2 operator*(const Vector2& left, const Vector2& right);		// 乗算　
