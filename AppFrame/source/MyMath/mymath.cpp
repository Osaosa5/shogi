#include "mymath.h"

// 当たり判定用。2つの円が当たったかを判定
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitCircle(
	float x1, float y1, float r1,		// ひとつめのcircle 中心(x,y), 半径r
	float x2, float y2, float r2		// ふたつめのcircle 中心(x,y), 半径r
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
