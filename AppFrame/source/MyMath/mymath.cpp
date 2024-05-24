#include "mymath.h"

// �����蔻��p�B2�̉~�������������𔻒�
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
int IsHitCircle(
	float x1, float y1, float r1,		// �ЂƂ߂�circle ���S(x,y), ���ar
	float x2, float y2, float r2		// �ӂ��߂�circle ���S(x,y), ���ar
) {
	float w, h, r;
	w = x1 - x2;
	h = y1 - y2;
	r = r1 + r2;
	if (r * r > w * w + h * h) {
		return 1;
	}
	return 0;
}
