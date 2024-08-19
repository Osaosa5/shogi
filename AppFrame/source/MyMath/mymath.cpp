
#include "mymath.h"

/**
	@brief	�_�Ƌ�`�̓����蔻��
	@param	x1	�_��x���W
	@param	y1	�_��y���W
	@param	x2	��`�̍����x���W
	@param	y2	��`�̍����y���W
	@param	w	��`�̕�
	@param	h	��`�̍���
	@return	true:�������Ă��� false:�������Ă��Ȃ�
*/
bool IsHitDotBox(int x1, int y1, int x2, int y2, int w, int h)
{
	return (x1 > x2 && x1 < x2 + w && y1 > y2 && y1 < y2 + h);
}

/**
	@brief	�_�Ƌ�`�̓����蔻��
	@param	dot	�_�̍��W
	@param	box	��`�̍��W
	@return	true:�������Ă��� false:�������Ă��Ȃ�
*/
bool IsHitDotBox(Dot dot, Box box)
{
	return (dot.x > box.x && dot.x < box.x + box.w && dot.y > box.y && dot.y < box.y + box.h);
}

/**
	@brief	��`�Ƌ�`�̓����蔻��
	@param	x1	��`1�̍����x���W
	@param	y1	��`1�̍����y���W
	@param	w1	��`1�̕�
	@param	h1	��`1�̍���
	@param	x2	��`2�̍����x���W
	@param	y2	��`2�̍����y���W
	@param	w2	��`2�̕�
	@param	h2	��`2�̍���
	@return	true:�������Ă��� false:�������Ă��Ȃ�
*/
bool IsHitBox(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	return (x1 < x2 + w2 && x2 < x1 + w1 && y1 < y2 + h2 && y2 < y1 + h1);
}

/**
	@brief	��`�Ƌ�`�̓����蔻��
	@param	box1	��`1
	@param	box2	��`2
	@return	true:�������Ă��� false:�������Ă��Ȃ�
*/
bool IsHitBox(Box box1, Box box2)
{
	return (box1.x < box2.x + box2.w && box2.x < box1.x + box1.w && box1.y < box2.y + box2.h && box2.y < box1.y + box1.h);
}

/**
	@brief	�~�Ɖ~�̓����蔻��
	@param	x1	�~1�̒��Sx
	@param	y1	�~1�̒��Sy
	@param	r1	�~1�̔��a
	@param	x2	�~2�̒��Sx
	@param	y2	�~2�̒��Sy
	@param	r2	�~2�̔��a
	@return	true:�������Ă��� false:�������Ă��Ȃ�
*/
bool IsHitCircle(
	float x1, float y1, float r1,		// �ЂƂ߂�circle ���S(x,y), ���ar
	float x2, float y2, float r2		// �ӂ��߂�circle ���S(x,y), ���ar
) {
	float w, h, r;
	w = x1 - x2;
	h = y1 - y2;
	r = r1 + r2;

	return w * w + h * h <= r * r;
}

/**
	@brief	�~�Ɖ~�̓����蔻��
	@param	c1	�~1
	@param	c2	�~2
	@return	true:�������Ă��� false:�������Ă��Ȃ�
*/
bool IsHitCircle(Circle c1, Circle c2)
{
	float w, h, r;
	w = c1.x - c2.x;
	h = c1.y - c2.y;
	r = c1.r + c2.r;

	return w * w + h * h <= r * r;
}
