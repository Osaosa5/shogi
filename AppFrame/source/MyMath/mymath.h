#include <math.h>

#include "Shape.h"

// �v�Z�p�}�N��
#define	PI	(3.1415926535897932386f)
#define	DEG2RAD(x)			( ((x) / 180.0f ) * PI )
#define	RAD2DEG(x)			( ((x) * 180.0f ) / PI )

bool IsHitDotBox(
	int x1, int y1,					// �_�̍��W
	int x2, int y2, int w, int h	// ��`�̍��W
);

bool IsHitDotBox(
	Dot dot,	// �_�̍��W
	Box box		// ��`�̍��W
);

bool IsHitBox(
	int x1, int y1, int w1, int h1,	// �ЂƂ߂̋�`�̍��W
	int x2, int y2, int w2, int h2	// �ӂ��߂̋�`�̍��W
);

bool IsHitBox(
	Box box1,	// �ЂƂ߂̋�`�̍��W
	Box box2	// �ӂ��߂̋�`�̍��W
);

bool IsHitCircle(
	float x1, float y1, float r1,		// �ЂƂ߂�circle ���S(x,y), ���ar
	float x2, float y2, float r2		// �ӂ��߂�circle ���S(x,y), ���ar
);

bool IsHitCircle(
	Circle c1,
	Circle c2
);
