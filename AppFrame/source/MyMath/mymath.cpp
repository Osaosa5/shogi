#include "mymath.h"

// “–‚½‚è”»’è—pB2‚Â‚Ì‰~‚ª“–‚½‚Á‚½‚©‚ğ”»’è
// “–‚½‚Á‚Ä‚¢‚½‚ç1, “–‚½‚Á‚Ä‚¢‚È‚©‚Á‚½‚ç0‚ğ•Ô‚·
int IsHitCircle(
	float x1, float y1, float r1,		// ‚Ğ‚Æ‚Â‚ß‚Ìcircle ’†S(x,y), ”¼Œar
	float x2, float y2, float r2		// ‚Ó‚½‚Â‚ß‚Ìcircle ’†S(x,y), ”¼Œar
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
