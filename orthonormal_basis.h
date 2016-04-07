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
			data[0] = u;
			data[1] = v;
			data[2] = w;
		}

		vector3& u()
		{
			return data[0];
		}

		vector3& v()
		{
			return data[1];
		}

		vector3& w()
		{
			return data[2];
		}

		const vector3& u() const
		{
			return data[0];
		}

		const vector3& v() const
		{
			return data[1];
		}

		const vector3& w() const
		{
			return data[2];
		}

		inline void set(const vector3& u, const vector3& v, const vector3& w)
		{
			data[0] = u;
			data[1] = v;
			data[2] = w;
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
		vector3 data[3];
	};

	inline bool operator==(const orthonormal_basis& o1, const orthonormal_basis& o2)
	{
		return (o1.data[0] == o2.data[0] && o1.data[1] == o2.data[1] && o1.data[2] == o2.data[2]);
	}

	inline bool operator!=(const orthonormal_basis& o1, const orthonormal_basis& o2)
	{
		return (o1.data[0] != o2.data[0] || o1.data[1] != o2.data[1] || o1.data[2] != o2.data[2]);
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
		return (os << o.data[0] << o.data[1] << o.data[2]);
	}
}

#endif
