#ifndef _SAMPLE1_H
#define _SAMPLE1_H

#include "random.h"

namespace galileo
{
	class c_sample1
	{
	public:
		virtual int generate(t_float* samples) = 0;
	};

	class c_jitter_sample1 : public c_sample1
	{
	public:
		c_jitter_sample1(int _ns);
		virtual int generate(t_float* samples);

	public:
		int ns;
		c_random* rnd;
	};
}

#endif
