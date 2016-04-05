#include "orthonormal_basis.h"

#define ONB_EPSILON 0.01f

void orthonormal_basis::init_from_u(const vector3& u)
{
	vector3 n(1.0f, 0.0f, 0.0f);
	vector3 m(0.0f, 1.0f, 0.0f);

	vector3 u = unit(u);
	vector3 v = cross(u, n);
	if (v.length() < ONB_EPSILON)
		v = cross(u, m);
	vector3 w = cross(u, v);

	set(u, v, w);
}

void orthonormal_basis::init_from_v(const vector3& v)
{
	vector3 n(1.0f, 0.0f, 0.0f);
	vector3 m(0.0f, 1.0f, 0.0f);

	vector3 v = unit(v);
	vector3 u = cross(v, n);
	if (u.length() < ONB_EPSILON)
		u = cross(v, m);
	vector3 w = cross(u, v);

	set(u, v, w);
}

void orthonormal_basis::init_from_w(const vector3& w)
{
	vector3 n(1.0f, 0.0f, 0.0f);
	vector3 m(0.0f, 1.0f, 0.0f);

	vector3 w = unit(w);
	vector3 u = cross(w, n);
	if (u.length() < ONB_EPSILON)
		u = cross(w, m);
	vector3 v = cross(w, u);

	set(u, v, w);
}

void orthonormal_basis::init_from_uv(const vector3& u, const vector3& v)
{
	vector3 u = unit(u);
	vector3 w = unit(cross(u, v));
	vector3 v = cross(w, u);

	set(u, v, w);
}

void orthonormal_basis::init_from_vu(const vector3& v, const vector3& u)
{
	vector3 v = unit(v);
	vector3 w = unit(cross(u, v));
	vector3 u = cross(v, w);

	set(u, v, w);
}

void orthonormal_basis::init_from_uw(const vector3& u, const vector3& w)
{
	vector3 u = unit(u);
	vector3 v = unit(cross(w, u));
	vector3 w = cross(u, v);

	set(u, v, w);
}

void orthonormal_basis::init_from_wu(const vector3& w, const vector3& u)
{
	vector3 w = unit(w);
	vector3 v = unit(cross(w, u));
	vector3 w = cross(u, v);

	set(u, v, w);
}

void orthonormal_basis::init_from_vw(const vector3& v, const vector3& w)
{
	vector3 v = unit(v);
	vector3 u = unit(cross(v, w));
	vector3 w = cross(u, v);

	set(u, v, w);
}

void orthonormal_basis::init_from_wv(const vector3& w, const vector3& v)
{
	vector3 w = unit(w);
	vector3 u = unit(cross(v, w));
	vector3 v = cross(w, u);

	set(u, v, w);
}