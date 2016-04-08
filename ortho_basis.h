#ifndef _ORTHONORMAL_BASIS_H
#define _ORTHONORMAL_BASIS_H

#include "vector3.h"

namespace galileo
{
	class c_ortho_basis
	{
	public:
		c_ortho_basis()
		{
		}

		c_ortho_basis(const c_vector3& u, const c_vector3& v, const c_vector3& w)
		{
			data[0] = u;
			data[1] = v;
			data[2] = w;
		}

		c_vector3& u()
		{
			return data[0];
		}

		c_vector3& v()
		{
			return data[1];
		}

		c_vector3& w()
		{
			return data[2];
		}

		const c_vector3& u() const
		{
			return data[0];
		}

		const c_vector3& v() const
		{
			return data[1];
		}

		const c_vector3& w() const
		{
			return data[2];
		}

		inline void set(const c_vector3& u, const c_vector3& v, const c_vector3& w)
		{
			data[0] = u;
			data[1] = v;
			data[2] = w;
		}

		void init_from_u(const c_vector3& u);
		void init_from_v(const c_vector3& v);
		void init_from_w(const c_vector3& w);

		void init_from_uv(const c_vector3& u, const c_vector3& v);
		void init_from_vu(const c_vector3& v, const c_vector3& u);

		void init_from_uw(const c_vector3& u, const c_vector3& w);
		void init_from_wu(const c_vector3& w, const c_vector3& u);

		void init_from_vw(const c_vector3& v, const c_vector3& w);
		void init_from_wv(const c_vector3& w, const c_vector3& v);

	public:
		c_vector3 data[3];
	};

	inline bool operator==(const c_ortho_basis& o1, const c_ortho_basis& o2)
	{
		return (o1.data[0] == o2.data[0] && o1.data[1] == o2.data[1] && o1.data[2] == o2.data[2]);
	}

	inline bool operator!=(const c_ortho_basis& o1, const c_ortho_basis& o2)
	{
		return (o1.data[0] != o2.data[0] || o1.data[1] != o2.data[1] || o1.data[2] != o2.data[2]);
	}

	inline std::istream& operator>>(std::istream& is, c_ortho_basis& o)
	{
		c_vector3 u, v, w;
		is >> u >> v >> w;
		o.init_from_uv(u, w);
		return is;
	}

	inline std::ostream& operator<<(std::ostream& os, const c_ortho_basis& o)
	{
		return (os << o.data[0] << o.data[1] << o.data[2]);
	}
}

#endif
