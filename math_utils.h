#ifndef _MATH_UTILS_H
#define _MATH_UTILS_H

#include <math.h>
#include "global_define.h"

inline bool fequal(FLOAT f1, FLOAT f2)
{
	return fabs(f1 - f2) <= FLOAT_EPSILON;
}

#endif