#ifndef _SAMPLE2_H
#define _SAMPLE2_H

#include "vector2.h"
#include "random.h"

namespace galileo
{
	class c_sample2 
	{
	public:
		virtual int generate(c_vector2* a) = 0;
	};
	
	class c_jitter_sample2 : public c_sample2 
	{
	public:
		c_jitter_sample2(int _m, int _n);
		virtual int generate(c_vector2* a);

	public:
		int m, n;
		c_random* rnd;
	};

	class c_ham_sample2 : public c_sample2
	{
	public:
		c_ham_sample2(int _num);
		virtual int generate(c_vector2* a);

	public:
		int n;
		c_random* rnd;
	};
}

#endif