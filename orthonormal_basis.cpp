#include "orthonormal_basis.h"

#define ONB_EPSILON 0.01f

#define U basis[0]
#define V basis[1]
#define W basis[2]

void galileo::orthonormal_basis::init_from_u(const vector3& u)
{
	vector3 n(1.0f, 0.0f, 0.0f);
	vector3 m(0.0f, 1.0f, 0.0f);

	U = normalize(u);
	V = cross(U, n);
	if (V.length() < ONB_EPSILON)
		V = cross(U, m);
	W = cross(U, V);
}

void galileo::orthonormal_basis::init_from_v(const vector3& v)
{
	vector3 n(1.0f, 0.0f, 0.0f);
	vector3 m(0.0f, 1.0f, 0.0f);

	V = normalize(v);
	U = cross(V, n);
	if (U.length() < ONB_EPSILON)
		U = cross(V, m);
	W = cross(U, V);
}

void galileo::orthonormal_basis::init_from_w(const vector3& w)
{
	vector3 n(1.0f, 0.0f, 0.0f);
	vector3 m(0.0f, 1.0f, 0.0f);

	W = normalize(w);
	U = cross(W, n);
	if (U.length() < ONB_EPSILON)
		U = cross(W, m);
	V = cross(W, U);
}

void galileo::orthonormal_basis::init_from_uv(const vector3& u, const vector3& v)
{
	U = normalize(u);
	W = normalize(cross(u, v));
	V = cross(W, U);
}

void galileo::orthonormal_basis::init_from_vu(const vector3& v, const vector3& u)
{
	V = normalize(v);
	W = normalize(cross(u, v));
	U = cross(V, W);
}

void galileo::orthonormal_basis::init_from_uw(const vector3& u, const vector3& w)
{
	U = normalize(u);
	V = normalize(cross(w, u));
	W = cross(U, W);
}

void galileo::orthonormal_basis::init_from_wu(const vector3& w, const vector3& u)
{
	W = normalize(w);
	V = normalize(cross(w, u));
	U = cross(V, W);
}

void galileo::orthonormal_basis::init_from_vw(const vector3& v, const vector3& w)
{
	V = normalize(v);
	U = normalize(cross(v, w));
	W = cross(U, V);
}

void galileo::orthonormal_basis::init_from_wv(const vector3& w, const vector3& v)
{
	W = normalize(w);
	U = normalize(cross(v, w));
	V = cross(W, U);
}