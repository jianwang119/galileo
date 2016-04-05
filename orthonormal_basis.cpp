#include "orthonormal_basis.h"

#define ONB_EPSILON 0.01f

#define U basis[0]
#define V basis[1]
#define W basis[2]

void orthonormal_basis::init_from_u(const vector3& u)
{
	vector3 n(1.0f, 0.0f, 0.0f);
	vector3 m(0.0f, 1.0f, 0.0f);

	U = unit(u);
	V = cross(U, n);
	if (V.length() < ONB_EPSILON)
		V = cross(U, m);
	W = cross(U, V);
}

void orthonormal_basis::init_from_v(const vector3& v)
{
	vector3 n(1.0f, 0.0f, 0.0f);
	vector3 m(0.0f, 1.0f, 0.0f);

	V = unit(v);
	U = cross(V, n);
	if (U.length() < ONB_EPSILON)
		U = cross(V, m);
	W = cross(U, V);
}

void orthonormal_basis::init_from_w(const vector3& w)
{
	vector3 n(1.0f, 0.0f, 0.0f);
	vector3 m(0.0f, 1.0f, 0.0f);

	W = unit(w);
	U = cross(W, n);
	if (U.length() < ONB_EPSILON)
		U = cross(W, m);
	V = cross(W, U);
}

void orthonormal_basis::init_from_uv(const vector3& u, const vector3& v)
{
	U = unit(u);
	W = unit(cross(u, v));
	V = cross(W, U);
}

void orthonormal_basis::init_from_vu(const vector3& v, const vector3& u)
{
	V = unit(v);
	W = unit(cross(u, v));
	U = cross(V, W);
}

void orthonormal_basis::init_from_uw(const vector3& u, const vector3& w)
{
	U = unit(u);
	V = unit(cross(w, u));
	W = cross(U, W);
}

void orthonormal_basis::init_from_wu(const vector3& w, const vector3& u)
{
	W = unit(w);
	V = unit(cross(w, u));
	U = cross(V, W);
}

void orthonormal_basis::init_from_vw(const vector3& v, const vector3& w)
{
	V = unit(v);
	U = unit(cross(v, w));
	W = cross(U, V);
}

void orthonormal_basis::init_from_wv(const vector3& w, const vector3& v)
{
	W = unit(w);
	U = unit(cross(v, w));
	V = cross(W, U);
}