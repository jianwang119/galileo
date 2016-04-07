#ifndef _MATH_UTILS_H
#define _MATH_UTILS_H

#include <math.h>
#include "global_define.h"

template<typename T>
T clamp(T f, T min, T max)
{
	T v = f;
	if (v > max)
		v = max;
	if (v < min)
		v = min;
	return f;
}

template<typename T>
T lerp(T s, T e, FLOAT f)
{
	return s * f + e * (1 - f);
}

inline FLOAT fclamp01(FLOAT f)
{
	return clamp<FLOAT>(f, 0.0f, 1.0f);
}

inline bool fequal(FLOAT f1, FLOAT f2)
{
	return fabs(f1 - f2) <= FLOAT_EPSILON;
}

#endif