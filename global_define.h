#ifndef _GLOBAL_DEFINE_
#define _GLOBAL_DEFINE_

#include <stdlib.h>
#include <iostream>

typedef unsigned char t_u8;
typedef signed char t_s8;
typedef unsigned short t_u16;
typedef signed short t_s16;
typedef unsigned int t_u32;
typedef signed int t_s32;
typedef unsigned long long t_u64;
typedef signed long long t_s64;
#ifdef HIGH_PRECISION
typedef double t_float;
#else
typedef float t_float;
#endif

#endif