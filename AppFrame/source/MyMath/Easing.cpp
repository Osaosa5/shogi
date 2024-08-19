
#include "Easing.h"

// イージング
float EasingLinear(float cnt, float start, float end, float frames) 
{
    return (end - start) * cnt / frames + start;
}

float EasingInQuad(float cnt, float start, float end, float frames) 
{
    cnt /= frames;
    return (end - start) * cnt * cnt + start;
}

float EasingOutQuad(float cnt, float start, float end, float frames) 
{
    cnt /= frames;
    return -(end - start) * cnt * (cnt - 2) + start;
}

float EasingInOutQuad(float cnt, float start, float end, float frames) 
{
    cnt /= frames / 2.0;
    if (cnt < 1) {
        return (end - start) / 2.0 * cnt * cnt + start;
    }
    cnt--;
    return -(end - start) / 2.0 * (cnt * (cnt - 2) - 1) + start;
}

float EasingInCubic(float cnt, float start, float end, float frames) 
{
    cnt /= frames;
    return (end - start) * cnt * cnt * cnt + start;
}

float EasingOutCubic(float cnt, float start, float end, float frames) 
{
    cnt /= frames;
    cnt--;
    return (end - start) * (cnt * cnt * cnt + 1) + start;
}

float EasingInOutCubic(float cnt, float start, float end, float frames) 
{
    cnt /= frames / 2.0;
    if (cnt < 1) {
        return (end - start) / 2.0 * cnt * cnt * cnt + start;
    }
    cnt -= 2;
    return (end - start) / 2.0 * (cnt * cnt * cnt + 2) + start;
}

float EasingInQuart(float cnt, float start, float end, float frames) 
{
    cnt /= frames;
    return (end - start) * cnt * cnt * cnt * cnt + start;
}

float EasingOutQuart(float cnt, float start, float end, float frames)
{
    cnt /= frames;
    cnt--;
    return -(end - start) * (cnt * cnt * cnt * cnt - 1) + start;
}

float EasingInOutQuart(float cnt, float start, float end, float frames) 
{
    cnt /= frames / 2.0;
    if (cnt < 1) {
        return (end - start) / 2.0 * cnt * cnt * cnt * cnt + start;
    }
    cnt -= 2;
    return -(end - start) / 2.0 * (cnt * cnt * cnt * cnt - 2) + start;
}

float EasingInQuint(float cnt, float start, float end, float frames)
{
    cnt /= frames;
    return (end - start) * cnt * cnt * cnt * cnt * cnt + start;
}

float EasingOutQuint(float cnt, float start, float end, float frames) 
{
    cnt /= frames;
    cnt--;
    return (end - start) * (cnt * cnt * cnt * cnt * cnt + 1) + start;
}

float EasingInOutQuint(float cnt, float start, float end, float frames) 
{
    cnt /= frames / 2.0;
    if (cnt < 1) {
        return (end - start) / 2.0 * cnt * cnt * cnt * cnt * cnt + start;
    }
    cnt -= 2;
    return (end - start) / 2.0 * (cnt * cnt * cnt * cnt * cnt + 2) + start;
}

float EasingInSine(float cnt, float start, float end, float frames) 
{
    return -(end - start) * cos(cnt / frames * (PIOver2)) + end + start;
}

float EasingOutSine(float cnt, float start, float end, float frames) 
{
    return (end - start) * sin(cnt / frames * PIOver2) + start;
}

float EasingInOutSine(float cnt, float start, float end, float frames) 
{
    return -(end - start) / 2.0 * (cos(PI * cnt / frames) - 1) + start;
}

float EasingInExpo(float cnt, float start, float end, float frames) 
{
    return (end - start) * pow(2.0, 10 * (cnt / frames - 1)) + start;
}

float EasingOutExpo(float cnt, float start, float end, float frames)
{
    return (end - start) * (-pow(2.0, -10 * cnt / frames) + 1) + start;
}

float EasingInOutExpo(float cnt, float start, float end, float frames) 
{
    cnt /= frames / 2.0;
    if (cnt < 1) {
        return (end - start) / 2.0 * pow(2.0, 10 * (cnt - 1)) + start;
    }
    cnt--;
    return (end - start) / 2.0 * (-pow(2.0, -10 * cnt) + 2) + start;
}

float EasingInCirc(float cnt, float start, float end, float frames) 
{
    cnt /= frames;
    return -(end - start) * (sqrt(1 - cnt * cnt) - 1) + start;
}

float EasingOutCirc(float cnt, float start, float end, float frames) 
{
    cnt /= frames;
    cnt--;
    return (end - start) * sqrt(1 - cnt * cnt) + start;
}

float EasingInOutCirc(float cnt, float start, float end, float frames) 
{
    cnt /= frames / 2.0;
    if (cnt < 1) {
        return -(end - start) / 2.0 * (sqrt(1 - cnt * cnt) - 1) + start;
    }
    cnt -= 2;
    return (end - start) / 2.0 * (sqrt(1 - cnt * cnt) + 1) + start;
}
