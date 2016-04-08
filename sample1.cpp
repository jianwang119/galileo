
#include "sample1.h"
#include "utils.h"

galileo::c_jitter_sample1::c_jitter_sample1(int _ns)
{
	ns = _ns;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	rnd = new c_random(tv.tv_usec);
}

int galileo::c_jitter_sample1::generate(t_float* samples)
{
	for (int i = 0; i < ns; i++)
		samples[i] = t_float(i) / t_float(ns) + t_float((*rnd)()) / t_float(ns);

	// shuffle
	for (int i = ns - 2; i >= 0; i--)
	{
		int target = int(t_float((*rnd)()) * t_float(i));
		t_float temp = samples[i + 1];
		samples[i + 1] = samples[target];
		samples[target] = temp;
	}
	return ns;
}

