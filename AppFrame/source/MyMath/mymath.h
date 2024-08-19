#include <math.h>

#include "Shape.h"

// 計算用マクロ
#define	PI	(3.1415926535897932386f)
#define	DEG2RAD(x)			( ((x) / 180.0f ) * PI )
#define	RAD2DEG(x)			( ((x) * 180.0f ) / PI )

bool IsHitDotBox(
	int x1, int y1,					// 点の座標
	int x2, int y2, int w, int h	// 矩形の座標
);

bool IsHitDotBox(
	Dot dot,	// 点の座標
	Box box		// 矩形の座標
);

bool IsHitBox(
	int x1, int y1, int w1, int h1,	// ひとつめの矩形の座標
	int x2, int y2, int w2, int h2	// ふたつめの矩形の座標
);

bool IsHitBox(
	Box box1,	// ひとつめの矩形の座標
	Box box2	// ふたつめの矩形の座標
);

bool IsHitCircle(
	float x1, float y1, float r1,		// ひとつめのcircle 中心(x,y), 半径r
	float x2, float y2, float r2		// ふたつめのcircle 中心(x,y), 半径r
);

bool IsHitCircle(
	Circle c1,
	Circle c2
);
