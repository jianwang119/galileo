#ifndef _RANDOM_H
#define _RANDOM_H

#include "global_define.h"

// linear congruence algorithm
class random
{
public:
	random(U64 _seed = 7654321ULL)
	{
		seed = _seed;
		mult = 62089911ULL;
		u64_max = 4294967295ULL;
		float_max = 4294967295.0f;
	}

	inline FLOAT operator()()
	{
		seed = mult * seed;
		return FLOAT(seed % u64_max) / float_max;
	}

public:
	U64 seed;
	U64 mult;
	U64 u64_max;
	FLOAT float_max;
};

#endif