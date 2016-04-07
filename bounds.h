#ifndef _BOUNDS_H
#define _BOUNDS_H

#include "math_utils.h"
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

	inline bool bounds::ray_intersect(const ray& r, FLOAT tmin, FLOAT tmax) const
	{
		float interval_min = tmin;
		float interval_max = tmax;

		float t0 = (pp[r.posneg[0]].x() - r.origin().x()) * r.direction_inv().x();
		float t1 = (pp[r.posneg[1]].x() - r.origin().x()) * r.direction_inv().x();
		if (t0 > interval_min) interval_min = t0;
		if (t1 < interval_max) interval_max = t1;
		if (interval_min > interval_max) 
			return false;

		t0 = (pp[r.posneg[2]].y() - r.origin().y()) * r.direction_inv().y();
		t1 = (pp[r.posneg[3]].y() - r.origin().y()) * r.direction_inv().y();
		if (t0 > interval_min) interval_min = t0;
		if (t1 < interval_max) interval_max = t1;
		if (interval_min > interval_max) 
			return false;

		t0 = (pp[r.posneg[4]].z() - r.origin().z()) * r.direction_inv().z();
		t1 = (pp[r.posneg[5]].z() - r.origin().z()) * r.direction_inv().z();
		if (t0 > interval_min) interval_min = t0;
		if (t1 < interval_max) interval_max = t1;
		if (interval_min > interval_max)
			return false;

		return true;
	}

	inline bounds surround(const bounds& b1, const bounds& b2)
	{
		return bounds(min(b1.min(), b2.min()), max(b1.max(), b2.max()));
	}
}

#endif
