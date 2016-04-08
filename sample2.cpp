
#include "sample2.h"
#include "utils.h"

galileo::c_jitter_sample2::c_jitter_sample2(int _m, int _n)
{
	m = _m;
	n = _n;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	rnd = new c_random(tv.tv_usec);
}

int galileo::c_jitter_sample2::generate(c_vector2* a)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			a[i*n + j] = c_vector2((i + (*rnd)()) / m, (j + (*rnd)()) / n);

	// shuffle
	for (int i = m*n - 2; i >= 0; i--) 
	{
		int target = int(t_float((*rnd)()) * t_float(i));
		c_vector2 temp = a[i + 1];
		a[i + 1] = a[target];
		a[target] = temp;
	}
	return m*n;
}

galileo::c_ham_sample2::c_ham_sample2(int _num)
{
	n = _num;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	rnd = new c_random(tv.tv_usec);
}

int galileo::c_ham_sample2::generate(c_vector2* a)
{
	t_float p, u, v;
	t_float offu = (*rnd)();
	t_float offv = (*rnd)();

	for (int k = 0; k < n; k++)
	{
		u = 0.0f;
		p = 0.5f;
		for (int kk = k; kk; p *= 0.5, kk >>= 1)
			if (kk & 1) u += p; // kk mod 2 == 1 

		v = ((t_float)k + 0.5f) / (t_float)n;
		u += offu;
		v += offv;
		u -= int(u);
		v -= int(v);
		a[k] = c_vector2(u, v);
	}
	return n;
}
