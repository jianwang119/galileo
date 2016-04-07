#ifndef _ORTHONORMAL_BASIS_H
#define _ORTHONORMAL_BASIS_H

#include "vector3.h"

namespace galileo
{
	class orthonormal_basis
	{
	public:
		orthonormal_basis()
		{
		}

		orthonormal_basis(const vector3& u, const vector3& v, const vector3& w)
		{
			basis[0] = u;
			basis[1] = v;
			basis[2] = w;
		}

		vector3& u()
		{
			return basis[0];
		}

		const vector3& u() const
		{
			return basis[0];
		}

		vector3& v()
		{
			return basis[1];
		}

		const vector3& v() const
		{
			return basis[1];
		}

		vector3& w()
		{
			return basis[2];
		}

		const vector3& w() const
		{
			return basis[2];
		}

		inline void set(const vector3& u, const vector3& v, const vector3& w)
		{
			basis[0] = u;
			basis[1] = v;
			basis[2] = w;
		}

		void init_from_u(const vector3& u);
		void init_from_v(const vector3& v);
		void init_from_w(const vector3& w);

		void init_from_uv(const vector3& u, const vector3& v);
		void init_from_vu(const vector3& v, const vector3& u);

		void init_from_uw(const vector3& u, const vector3& w);
		void init_from_wu(const vector3& w, const vector3& u);

		void init_from_vw(const vector3& v, const vector3& w);
		void init_from_wv(const vector3& w, const vector3& v);

	public:
		vector3 basis[3];
	};


	inline bool operator==(const orthonormal_basis& o1, const orthonormal_basis& o2)
	{
		return (o1.basis[0] == o2.basis[0] && o1.basis[1] == o2.basis[1] && o1.basis[2] == o2.basis[2]);
	}

	inline bool operator!=(const orthonormal_basis& o1, const orthonormal_basis& o2)
	{
		return (o1.basis[0] != o2.basis[0] || o1.basis[1] != o2.basis[1] || o1.basis[2] != o2.basis[2]);
	}

	inline std::istream& operator>>(std::istream& is, orthonormal_basis& o)
	{
		vector3 u, v, w;
		is >> u >> v >> w;
		o.init_from_uv(u, w);
		return is;
	}

	inline std::ostream& operator<<(std::ostream& os, const orthonormal_basis& o)
	{
		return (os << o.basis[0] << o.basis[1] << o.basis[2]);
	}
}

#endif
