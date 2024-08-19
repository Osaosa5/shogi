
#include "mymath.h"

/**
	@brief	点と矩形の当たり判定
	@param	x1	点のx座標
	@param	y1	点のy座標
	@param	x2	矩形の左上のx座標
	@param	y2	矩形の左上のy座標
	@param	w	矩形の幅
	@param	h	矩形の高さ
	@return	true:当たっている false:当たっていない
*/
bool IsHitDotBox(int x1, int y1, int x2, int y2, int w, int h)
{
	return (x1 > x2 && x1 < x2 + w && y1 > y2 && y1 < y2 + h);
}

/**
	@brief	点と矩形の当たり判定
	@param	dot	点の座標
	@param	box	矩形の座標
	@return	true:当たっている false:当たっていない
*/
bool IsHitDotBox(Dot dot, Box box)
{
	return (dot.x > box.x && dot.x < box.x + box.w && dot.y > box.y && dot.y < box.y + box.h);
}

/**
	@brief	矩形と矩形の当たり判定
	@param	x1	矩形1の左上のx座標
	@param	y1	矩形1の左上のy座標
	@param	w1	矩形1の幅
	@param	h1	矩形1の高さ
	@param	x2	矩形2の左上のx座標
	@param	y2	矩形2の左上のy座標
	@param	w2	矩形2の幅
	@param	h2	矩形2の高さ
	@return	true:当たっている false:当たっていない
*/
bool IsHitBox(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	return (x1 < x2 + w2 && x2 < x1 + w1 && y1 < y2 + h2 && y2 < y1 + h1);
}

/**
	@brief	矩形と矩形の当たり判定
	@param	box1	矩形1
	@param	box2	矩形2
	@return	true:当たっている false:当たっていない
*/
bool IsHitBox(Box box1, Box box2)
{
	return (box1.x < box2.x + box2.w && box2.x < box1.x + box1.w && box1.y < box2.y + box2.h && box2.y < box1.y + box1.h);
}

/**
	@brief	円と円の当たり判定
	@param	x1	円1の中心x
	@param	y1	円1の中心y
	@param	r1	円1の半径
	@param	x2	円2の中心x
	@param	y2	円2の中心y
	@param	r2	円2の半径
	@return	true:当たっている false:当たっていない
*/
bool IsHitCircle(
	float x1, float y1, float r1,		// ひとつめのcircle 中心(x,y), 半径r
	float x2, float y2, float r2		// ふたつめのcircle 中心(x,y), 半径r
) {
	float w, h, r;
	w = x1 - x2;
	h = y1 - y2;
	r = r1 + r2;

	return w * w + h * h <= r * r;
}

/**
	@brief	円と円の当たり判定
	@param	c1	円1
	@param	c2	円2
	@return	true:当たっている false:当たっていない
*/
bool IsHitCircle(Circle c1, Circle c2)
{
	float w, h, r;
	w = c1.x - c2.x;
	h = c1.y - c2.y;
	r = c1.r + c2.r;

	return w * w + h * h <= r * r;
}
