#ifndef _RAY_H
#define _RAY_H

#include "vector3.h"

namespace galileo
{
	class c_ray
	{
	public:
		c_ray()
		{
		}

		c_ray(const c_vector3& o, const c_vector3& d)
		{
			data[0] = o;
			set_direction(d);
		}

		c_ray(const c_ray& r)
		{
			*this = r;
		}

		const c_vector3& origin() const
		{
			return data[0];
		}

		const c_vector3& direction() const
		{
			return data[1];
		}

		const c_vector3& direction_inv() const
		{
			return data[2];
		}

		void set_origin(const c_vector3& v)
		{
			data[0] = v;
		}

		void set_direction(const c_vector3& v)
		{
			data[1] = v;
			data[2] = c_vector3(1.0f / v.x(), 1.0f / v.y(), 1.0f / v.z());

			posneg[0] = (data[1].x() > 0 ? 0 : 1);
			posneg[1] = posneg[0] ^ 1;

			posneg[2] = (data[1].y() > 0 ? 0 : 1);
			posneg[3] = posneg[2] ^ 1;

			posneg[4] = (data[1].z() > 0 ? 0 : 1);
			posneg[5] = posneg[4] ^ 1;
		}

		c_vector3 get_point(t_float t) const
		{
			return data[0] + t * data[1];
		}

	public:
		c_vector3 data[3];
		int posneg[6];
	};

	inline std::ostream &operator<<(std::ostream &os, const c_ray &r)
	{
		return os << r.origin() << r.direction();
	}
}

#endif
