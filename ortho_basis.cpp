#include "ortho_basis.h"

#define ONB_EPSILON 0.01f

#define U data[0]
#define V data[1]
#define W data[2]

void galileo::c_ortho_basis::init_from_u(const c_vector3& u)
{
	c_vector3 n(1.0f, 0.0f, 0.0f);
	c_vector3 m(0.0f, 1.0f, 0.0f);

	U = normalize(u);
	V = cross(U, n);
	if (V.length() < ONB_EPSILON)
		V = cross(U, m);
	W = cross(U, V);
}

void galileo::c_ortho_basis::init_from_v(const c_vector3& v)
{
	c_vector3 n(1.0f, 0.0f, 0.0f);
	c_vector3 m(0.0f, 1.0f, 0.0f);

	V = normalize(v);
	U = cross(V, n);
	if (U.length() < ONB_EPSILON)
		U = cross(V, m);
	W = cross(U, V);
}

void galileo::c_ortho_basis::init_from_w(const c_vector3& w)
{
	c_vector3 n(1.0f, 0.0f, 0.0f);
	c_vector3 m(0.0f, 1.0f, 0.0f);

	W = normalize(w);
	U = cross(W, n);
	if (U.length() < ONB_EPSILON)
		U = cross(W, m);
	V = cross(W, U);
}

void galileo::c_ortho_basis::init_from_uv(const c_vector3& u, const c_vector3& v)
{
	U = normalize(u);
	W = normalize(cross(u, v));
	V = cross(W, U);
}

void galileo::c_ortho_basis::init_from_vu(const c_vector3& v, const c_vector3& u)
{
	V = normalize(v);
	W = normalize(cross(u, v));
	U = cross(V, W);
}

void galileo::c_ortho_basis::init_from_uw(const c_vector3& u, const c_vector3& w)
{
	U = normalize(u);
	V = normalize(cross(w, u));
	W = cross(U, W);
}

void galileo::c_ortho_basis::init_from_wu(const c_vector3& w, const c_vector3& u)
{
	W = normalize(w);
	V = normalize(cross(w, u));
	U = cross(V, W);
}

void galileo::c_ortho_basis::init_from_vw(const c_vector3& v, const c_vector3& w)
{
	V = normalize(v);
	U = normalize(cross(v, w));
	W = cross(U, V);
}

void galileo::c_ortho_basis::init_from_wv(const c_vector3& w, const c_vector3& v)
{
	W = normalize(w);
	U = normalize(cross(v, w));
	V = cross(W, U);
}