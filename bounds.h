#ifndef _BOUNDS_H
#define _BOUNDS_H

#include "ray.h"

namespace galileo
{
	class bounds
	{
	public:
		bounds()
		{
		}

		bounds(const vector3& min, const vector3& max)
		{
			pp[0] = min;
			pp[1] = max;
		}

		const vector3& min() const
		{
			return pp[0];
		}

		const vector3& max() const
		{
			return pp[1];
		}

		bool ray_intersect(const ray& r, FLOAT tmin, FLOAT tmax) const;

	protected:
		vector3 pp[2];
	};

	inline bounds surround(const bounds& b1, const bounds& b2)
	{
		return bounds(min(b1.min(), b2.min()), max(b1.max(), b2.max()));
	}
}

#endif
