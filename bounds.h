#ifndef _BOUNDS_H
#define _BOUNDS_H

#include "ray.h"

namespace galileo
{
	class c_bounds
	{
	public:
		c_bounds()
		{
		}

		c_bounds(const c_vector3& min, const c_vector3& max)
		{
			pp[0] = min;
			pp[1] = max;
		}

		const c_vector3& min() const
		{
			return pp[0];
		}

		const c_vector3& max() const
		{
			return pp[1];
		}

		bool ray_intersect(const c_ray& r, t_float tmin, t_float tmax) const;

	protected:
		c_vector3 pp[2];
	};

	inline c_bounds surround(const c_bounds& b1, const c_bounds& b2)
	{
		return c_bounds(min(b1.min(), b2.min()), max(b1.max(), b2.max()));
	}
}

#endif
