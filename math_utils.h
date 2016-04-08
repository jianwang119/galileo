#ifndef _MATH_UTILS_H
#define _MATH_UTILS_H

#include <math.h>
#include "global_define.h"

namespace galileo
{
	#define PI 3.14159265359f
	#define TWO_PI 6.28318530718f
	#define HALF_PI 1.570796326795f

	#define FLOAT_EPSILON 1.0e-5f

	template<typename T>
	void swap(T& t1, T& t2)
	{
		T tmp = t1;
		t1 = t2;
		t2 = tmp;
	}

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
	T lerp(T s, T e, t_float f)
	{
		return s * f + e * (1 - f);
	}

	template<typename T>
	T min(T t1, T t2)
	{
		return t1 < t2 ? t1 : t2;
	}

	template<typename T>
	T max(T t1, T t2)
	{
		return t1 > t2 ? t1 : t2;
	}

	inline t_float fdet3(t_float a, t_float b, t_float c, t_float d, t_float e, t_float f,
		t_float g, t_float h, t_float i)
	{
		return a*e*i + d*h*c + g*b*f - g*e*c - d*b*i - a*h*f;
	}

	inline t_float fclamp01(t_float f)
	{
		return clamp<t_float>(f, 0.0f, 1.0f);
	}

	inline bool fequal(t_float f1, t_float f2)
	{
		return fabs(f1 - f2) <= FLT_EPSILON;
	}
}

#endif