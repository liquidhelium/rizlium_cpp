#ifndef EASING_H
#define EASING_H
#include <functional>
#include <cmath>
#include <qdebug.h>
#define PI 3.141592654
typedef std::function<float(float)> Ease;
const Ease easing[16] =
{
	[](float x) {return x; },
	[](float x) {return sin((x * PI) / 2); },
	[](float x) {return 1 - cos((x * PI) / 2); },
	[](float x) {return -(cos(PI * x) - 1) / 2; },
	[](float x) {return x * x; },
	[](float x) {return 1 - (1 - x) * (1 - x); },
	[](float x) {return x < 0.5 ? 2 * x * x : 1 - pow(-2 * x + 2, 2) / 2; },
	[](float x) {return x * x * x; },
	[](float x) {return 1 - pow(1 - x, 3); },
	[](float x) {return x < 0.5 ? 4 * x * x * x : 1 - pow(-2 * x + 2, 3) / 2; },
	[](float x) {return x * x * x * x; },
	[](float x) {return 1 - pow(1 - x, 4); },
	[](float x) {return x < 0.5 ? 8 * x * x * x * x : 1 - pow(-2 * x + 2, 4) / 2; },
	[](float x) {return 0; },
	[](float x) {return 1; },
	[](float x) {qDebug() << "????ease, idk (AnimCurve¦Ä???)"; return 0; }
};

float inverseLerp(float val1, float val2, float midValue)
{
	return val2 > val1 ? (midValue - val1) / (val2 - val1) : 0;
}

float lerp(float val1, float val2, float progress)
{
	return (val2 - val1) * progress + val1;
}

float lerpWithEase(Ease func, float val1, float val2, float progress)
{
	return lerp(val1, val2, func(progress));
}

float liesBetween(float low, float high, float  value)
{
	return (value >= low) && (value < high);
}
#endif