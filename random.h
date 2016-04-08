#ifndef _RANDOM_H
#define _RANDOM_H

#include "global_define.h"

namespace galileo
{
	// linear congruence algorithm
	class c_random
	{
	public:
		c_random(t_u64 _seed = 7654321ULL)
		{
			seed = _seed;
			mult = 62089911ULL;
			u64_max = 4294967295ULL;
			flt_max = 4294967295.0f;
		}

		inline t_float operator()()
		{
			seed = mult * seed;
			return t_float(seed % u64_max) / flt_max;
		}

	public:
		t_u64 seed;
		t_u64 mult;
		t_u64 u64_max;
		t_float flt_max;
	};
}

#endif